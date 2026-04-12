#include "RadioBrowserStationProvider.h"

#include <array>
#include <ng-log/logging.h>
#include <QCoreApplication>
#include <QMetaObject>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>

namespace {

constexpr char const* RADIO_BROWSER_API_URL {"https://de1.api.radio-browser.info/json/stations/search"};

constexpr char const* RADIO_BROWSER_USER_AGENT {"Qlocky/1.0"};
constexpr int RADIO_BROWSER_LIMIT {100000};
constexpr std::size_t STATION_EMIT_BATCH_SIZE {100};

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

} // namespace

StationEntity toStationEntity(RadioBrowserApiStationRecord const& record) {
    std::string const streamUrl {record.url_resolved.empty() ? record.url : record.url_resolved};

    return StationEntity {
        Uuid {record.stationuuid},
        record.name,
        streamUrl,
        record.favicon,
        record.tags,
        record.language,
        record.countrycode,
        record.votes,
    };
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

RadioBrowserStationProvider::RadioBrowserStationProvider(RestApi& restApi) :
    m_restApi {restApi} {
}

Stream<StationEntity> RadioBrowserStationProvider::streamStations(StationFilter const& filter) {
    return Stream<StationEntity> {[this, filter](Stream<StationEntity>::Observer const& observer) {
        if (observer.isCanceled()) {
            return;
        }

        RestApiRequestOptions options {};
        options.url = createStationsUrl(filter);
        options.headers.push_back(RestApiHeader {"User-Agent", RADIO_BROWSER_USER_AGENT});

        m_restApi.get<RadioBrowserAPIv1>(options, [this, observer](Result<RadioBrowserAPIv1, RestApiCode> const& result) {
            handleStationsResponse(result, observer);
        });
    }};
}

void RadioBrowserStationProvider::handleStationsResponse(
    Result<RadioBrowserAPIv1, RestApiCode> const& result,
    Stream<StationEntity>::Observer const& observer) {
    if (result.isError()) {
        if (observer.isCanceled()) {
            return;
        }

        LOG(WARNING) << "Failed to fetch stations from radio-browser.info: " << describeRestApiError(result.error());
        observer.finish();
        return;
    }

    std::vector<StationEntity> stations {};
    std::size_t invalidUuidRecords {0};
    stations.reserve(result.value().stations.size());
    for (RadioBrowserApiStationRecord const& record : result.value().stations) {
        StationEntity const station {toStationEntity(record)};
        if (!station.id.isValid()) {
            ++invalidUuidRecords;
            continue;
        }

        stations.push_back(station);
    }

    LOG(INFO) << "Accepted " << stations.size() << " radio-browser stations.";
    if (invalidUuidRecords > 0) {
        LOG(WARNING) << "Rejected " << invalidUuidRecords << " radio-browser station records because of invalid UUIDs.";
    }

    emitStations(std::move(stations), observer);
}

void RadioBrowserStationProvider::emitStations(
    std::vector<StationEntity> stations,
    Stream<StationEntity>::Observer const& observer) const {
    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        return;
    }

    auto sharedStations = std::make_shared<std::vector<StationEntity>>(std::move(stations));
    QMetaObject::invokeMethod(application, [this, sharedStations, observer]() { emitStationBatch(sharedStations, 0, observer); }, Qt::QueuedConnection);
}

void RadioBrowserStationProvider::emitStationBatch(
    std::shared_ptr<std::vector<StationEntity>> const& stations,
    std::size_t nextIndex,
    Stream<StationEntity>::Observer const& observer) const {
    if (observer.isCanceled()) {
        return;
    }

    std::size_t currentIndex {nextIndex};
    std::size_t processedCount {0};
    while (currentIndex < stations->size() && processedCount < STATION_EMIT_BATCH_SIZE) {
        if (observer.isCanceled()) {
            return;
        }

        observer.publish(stations->at(currentIndex));
        ++currentIndex;
        ++processedCount;
    }

    if (currentIndex >= stations->size()) {
        observer.finish();
        return;
    }

    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        return;
    }

    QTimer::singleShot(0, application, [this, stations, currentIndex, observer]() {
        emitStationBatch(stations, currentIndex, observer);
    });
}

std::string RadioBrowserStationProvider::createStationsUrl(StationFilter const& filter) const {
    QUrl url {QString::fromUtf8(RADIO_BROWSER_API_URL)};
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