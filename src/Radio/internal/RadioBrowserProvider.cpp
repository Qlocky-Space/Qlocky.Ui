#include "RadioBrowserProvider.h"

#include <ng-log/logging.h>
#include <QCoreApplication>
#include <QMetaObject>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>

namespace {

constexpr char const* RADIO_BROWSER_PROVIDER_ID {"radio-browser"};
constexpr char const* RADIO_BROWSER_SEARCH_URL {"https://de1.api.radio-browser.info/json/stations/search"};
constexpr char const* RADIO_BROWSER_USER_AGENT {"Qlocky/1.0"};
constexpr int RADIO_BROWSER_LIMIT {1000};
constexpr std::size_t RESULT_EMIT_BATCH_SIZE {100};

std::string joinTags(std::vector<std::string> const& tags) {
    std::string result {};
    for (std::string const& tag : tags) {
        if (tag.empty()) {
            continue;
        }

        if (!result.empty()) {
            result += ",";
        }

        result += tag;
    }

    return result;
}

std::string describeRestApiError(RestApiCode code) {
    switch (code) {
        case RestApiCode::NetworkError:
            return "network-error";
        case RestApiCode::HttpError:
            return "http-error";
        case RestApiCode::ParseError:
            return "parse-error";
        case RestApiCode::InvalidUrl:
            return "invalid-url";
        case RestApiCode::Canceled:
            return "canceled";
        case RestApiCode::Unknown:
            return "unknown";
    }

    return "unknown";
}

} // namespace

RadioBrowserProvider::RadioBrowserProvider(RestApi& restApi) :
    m_restApi {restApi} {
}

std::string RadioBrowserProvider::providerId() const {
    return RADIO_BROWSER_PROVIDER_ID;
}

Stream<RadioSearchResult> RadioBrowserProvider::searchRadios(RadioSearchFilter const& filter) {
    return Stream<RadioSearchResult> {[this, filter](Stream<RadioSearchResult>::Observer const& observer) {
        if (observer.isCanceled() || filter.isEmpty()) {
            observer.finish();
            return;
        }

        RestApiRequestOptions options {};
        options.url = createSearchUrl(filter);
        options.headers.push_back(RestApiHeader {"User-Agent", RADIO_BROWSER_USER_AGENT});

        m_restApi.get<RadioBrowserAPIv1>(options, [this, observer](Result<RadioBrowserAPIv1, RestApiCode> const& result) {
            handleSearchResponse(result, observer);
        });
    }};
}

void RadioBrowserProvider::handleSearchResponse(
    Result<RadioBrowserAPIv1, RestApiCode> const& result,
    Stream<RadioSearchResult>::Observer const& observer) {
    if (result.isError()) {
        if (!observer.isCanceled()) {
            LOG(WARNING) << "Failed to fetch stations from radio-browser.info: " << describeRestApiError(result.error());
        }

        observer.finish();
        return;
    }

    auto results {std::make_shared<std::vector<RadioSearchResult>>()};
    std::size_t invalidRecords {0};
    results->reserve(result.value().stations.size());

    for (RadioBrowserApiStationRecord const& record : result.value().stations) {
        if (record.stationuuid.empty()) {
            ++invalidRecords;
            continue;
        }

        results->push_back(toSearchResult(record));
    }

    LOG(INFO) << "Accepted " << results->size() << " radio-browser stations.";
    if (invalidRecords > 0) {
        LOG(WARNING) << "Rejected " << invalidRecords << " radio-browser station records because of missing UUIDs.";
    }

    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        observer.finish();
        return;
    }

    QMetaObject::invokeMethod(application, [this, results, observer]() { emitBatch(results, 0, observer); }, Qt::QueuedConnection);
}

void RadioBrowserProvider::emitBatch(
    std::shared_ptr<std::vector<RadioSearchResult>> const& results,
    std::size_t nextIndex,
    Stream<RadioSearchResult>::Observer const& observer) const {
    if (observer.isCanceled()) {
        return;
    }

    std::size_t currentIndex {nextIndex};
    std::size_t processedCount {0};

    while (currentIndex < results->size() && processedCount < RESULT_EMIT_BATCH_SIZE) {
        if (observer.isCanceled()) {
            return;
        }

        observer.publish(results->at(currentIndex));
        ++currentIndex;
        ++processedCount;
    }

    if (currentIndex >= results->size()) {
        observer.finish();
        return;
    }

    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        observer.finish();
        return;
    }

    QTimer::singleShot(0, application, [this, results, currentIndex, observer]() {
        emitBatch(results, currentIndex, observer);
    });
}

RadioSearchResult RadioBrowserProvider::toSearchResult(RadioBrowserApiStationRecord const& record) const {
    std::string const streamUrl {record.url_resolved.empty() ? record.url : record.url_resolved};

    RadioEntity radio {
        makeRadioId(RADIO_BROWSER_PROVIDER_ID, record.stationuuid),
        record.name,
        RADIO_BROWSER_PROVIDER_ID,
        record.stationuuid,
        streamUrl,
    };

    return RadioSearchResult {
        radio,
        streamUrl,
        record.votes,
        record.favicon,
        record.language,
    };
}

std::string RadioBrowserProvider::createSearchUrl(RadioSearchFilter const& filter) const {
    QUrl url {QString::fromUtf8(RADIO_BROWSER_SEARCH_URL)};
    QUrlQuery query {};
    query.addQueryItem("hidebroken", "true");
    query.addQueryItem("limit", QString::number(RADIO_BROWSER_LIMIT));

    if (!filter.language.empty()) {
        query.addQueryItem("language", QString::fromStdString(filter.language));
    }

    if (!filter.country.empty()) {
        query.addQueryItem("country", QString::fromStdString(filter.country));
    }

    std::string const tagList {joinTags(filter.tags)};
    if (!tagList.empty()) {
        query.addQueryItem("tagList", QString::fromStdString(tagList));
    }

    if (filter.name.has_value() && !filter.name->empty()) {
        query.addQueryItem("name", QString::fromStdString(*filter.name));
    }

    url.setQuery(query);
    return url.toString(QUrl::FullyEncoded).toStdString();
}
