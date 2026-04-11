#include "RadioBrowserStationProvider.h"

#include <array>
#include <ng-log/logging.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <QCoreApplication>
#include <QMetaObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QUrlQuery>
#include <thread>

namespace {

constexpr std::array<char const*, 3> RADIO_BROWSER_API_URLS {{
    "https://all.api.radio-browser.info/json/stations",
    "https://de1.api.radio-browser.info/json/stations",
    "https://nl1.api.radio-browser.info/json/stations",
}};
constexpr char const* RADIO_BROWSER_USER_AGENT {"Qlocky/1.0"};
constexpr int RADIO_BROWSER_LIMIT {100000};
constexpr std::size_t STATION_EMIT_BATCH_SIZE {100};

struct RadioBrowserStationRecord {
    std::string stationuuid;
    std::string name;
    std::string url;
    std::string url_resolved;
    std::string favicon;
    std::string tags;
    std::string language;
    std::string countrycode;
    uint32_t votes {0};
};

std::string readString(nlohmann::json const& json, char const* key) {
    auto const it = json.find(key);
    if (it == json.end() || it->is_null()) {
        return {};
    }

    if (it->is_string()) {
        return it->get<std::string>();
    }

    if (it->is_number_integer()) {
        return std::to_string(it->get<std::int64_t>());
    }

    if (it->is_number_unsigned()) {
        return std::to_string(it->get<std::uint64_t>());
    }

    if (it->is_number_float()) {
        return std::to_string(it->get<double>());
    }

    if (it->is_boolean()) {
        return it->get<bool>() ? "true" : "false";
    }

    return {};
}

uint32_t readUInt32(nlohmann::json const& json, char const* key) {
    auto const it = json.find(key);
    if (it == json.end() || it->is_null()) {
        return 0;
    }

    if (it->is_number_unsigned()) {
        return it->get<uint32_t>();
    }

    if (it->is_number_integer()) {
        auto const value = it->get<std::int64_t>();
        return value > 0 ? static_cast<uint32_t>(value) : 0;
    }

    if (it->is_string()) {
        try {
            return static_cast<uint32_t>(std::stoul(it->get<std::string>()));
        }
        catch (...) {
            return 0;
        }
    }

    return 0;
}

std::optional<RadioBrowserStationRecord> parseRecord(nlohmann::json const& json) {
    if (!json.is_object()) {
        return std::nullopt;
    }

    RadioBrowserStationRecord record {};
    record.stationuuid = readString(json, "stationuuid");
    record.name = readString(json, "name");
    record.url = readString(json, "url");
    record.url_resolved = readString(json, "url_resolved");
    record.favicon = readString(json, "favicon");
    record.tags = readString(json, "tags");
    record.language = readString(json, "language");
    record.countrycode = readString(json, "countrycode");
    record.votes = readUInt32(json, "votes");

    if (record.stationuuid.empty()) {
        return std::nullopt;
    }

    return record;
}

StationEntity toStationEntity(RadioBrowserStationRecord const& record) {
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

void collectStationsFromJson(
    nlohmann::json const& value,
    std::vector<StationEntity>& stations,
    std::size_t& malformedRecords,
    std::size_t& invalidUuidRecords,
    std::size_t& acceptedRecords,
    std::size_t& visitedRecords) {
    if (value.is_array()) {
        for (nlohmann::json const& item : value) {
            collectStationsFromJson(item, stations, malformedRecords, invalidUuidRecords, acceptedRecords, visitedRecords);
        }
        return;
    }

    ++visitedRecords;

    try {
        std::optional<RadioBrowserStationRecord> const record {parseRecord(value)};
        if (!record.has_value()) {
            ++malformedRecords;
            return;
        }

        StationEntity const station {toStationEntity(record.value())};
        if (!station.id.isValid()) {
            ++invalidUuidRecords;
            return;
        }

        stations.push_back(station);
        ++acceptedRecords;
    }
    catch (std::exception const& ex) {
        LOG(WARNING) << "Failed to parse radio-browser station record at index " << (visitedRecords - 1) << ": " << ex.what();
        ++malformedRecords;
    }
}

std::string describeReplyFailure(QNetworkReply const& reply) {
    QStringList parts {};
    parts.push_back(reply.errorString());

    QVariant const statusCode {reply.attribute(QNetworkRequest::HttpStatusCodeAttribute)};
    if (statusCode.isValid()) {
        parts.push_back(QStringLiteral("status=%1").arg(statusCode.toInt()));
    }

    QVariant const reasonPhrase {reply.attribute(QNetworkRequest::HttpReasonPhraseAttribute)};
    if (reasonPhrase.isValid()) {
        parts.push_back(QStringLiteral("reason=%1").arg(reasonPhrase.toString()));
    }

    if (reply.url().isValid()) {
        parts.push_back(QStringLiteral("url=%1").arg(reply.url().toString()));
    }

    return parts.join(QStringLiteral(", ")).toStdString();
}

} // namespace

struct RadioBrowserStationProvider::StationFetchRequestState {
    Stream<StationEntity>::ItemHandler onStation {};
    Stream<StationEntity>::FinishedHandler onFinished {};
    Stream<StationEntity>::Subscription subscription {};
    std::size_t nextUrlIndex {0};
};

RadioBrowserStationProvider::RadioBrowserStationProvider() :
    m_networkAccessManager {} {
}

Stream<StationEntity> RadioBrowserStationProvider::streamAllStations() {
    return Stream<StationEntity> {[this](Stream<StationEntity>::ItemHandler onStation, Stream<StationEntity>::FinishedHandler onFinished, Stream<StationEntity>::Subscription const& subscription) {
        startNextRequest(createRequestState(std::move(onStation), std::move(onFinished), subscription));
    }};
}

std::shared_ptr<RadioBrowserStationProvider::StationFetchRequestState> RadioBrowserStationProvider::createRequestState(
    Stream<StationEntity>::ItemHandler onStation,
    Stream<StationEntity>::FinishedHandler onFinished,
    Stream<StationEntity>::Subscription const& subscription) const {
    auto requestState = std::make_shared<StationFetchRequestState>();
    requestState->onStation = std::move(onStation);
    requestState->onFinished = std::move(onFinished);
    requestState->subscription = subscription;
    return requestState;
}

void RadioBrowserStationProvider::startNextRequest(std::shared_ptr<StationFetchRequestState> const& state) {
    if (state->subscription.isCanceled()) {
        return;
    }

    if (state->nextUrlIndex >= RADIO_BROWSER_API_URLS.size()) {
        LOG(ERROR) << "Failed to fetch stations from radio-browser.info: all configured mirrors failed.";
        finishRequest(state);
        return;
    }

    QNetworkRequest const request {createNetworkRequest(createStationsUrl(state->nextUrlIndex))};
    ++state->nextUrlIndex;

    QNetworkReply* reply {m_networkAccessManager.get(request)};
    QObject::connect(reply, &QNetworkReply::finished, [this, reply, state]() {
        handleReplyFinished(reply, state);
    });
}

void RadioBrowserStationProvider::finishRequest(std::shared_ptr<StationFetchRequestState> const& state) const {
    if (state->subscription.isCanceled()) {
        return;
    }

    state->onFinished();
}

void RadioBrowserStationProvider::handleReplyFinished(
    QNetworkReply* reply,
    std::shared_ptr<StationFetchRequestState> const& state) {
    std::unique_ptr<QNetworkReply, void (*)(QNetworkReply*)> replyGuard(reply, [](QNetworkReply* currentReply) {
        if (currentReply != nullptr) {
            currentReply->deleteLater();
        }
    });

    if (reply->error() != QNetworkReply::NoError) {
        if (state->subscription.isCanceled()) {
            return;
        }

        LOG(WARNING) << "Failed to fetch stations from radio-browser.info mirror: " << describeReplyFailure(*reply);
        startNextRequest(state);
        return;
    }

    parseAndEmitStations(reply->readAll(), state);
}

void RadioBrowserStationProvider::parseAndEmitStations(
    QByteArray payload,
    std::shared_ptr<StationFetchRequestState> const& state) const {
    std::thread([this, payload, state]() mutable {
        if (state->subscription.isCanceled()) {
            return;
        }

        emitStations(parseStations(payload), state);
    }).detach();
}

void RadioBrowserStationProvider::emitStations(
    std::vector<StationEntity> stations,
    std::shared_ptr<StationFetchRequestState> const& state) const {
    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        return;
    }

    auto sharedStations = std::make_shared<std::vector<StationEntity>>(std::move(stations));
    QMetaObject::invokeMethod(application, [this, state, sharedStations]() { emitStationBatch(sharedStations, 0, state); }, Qt::QueuedConnection);
}

void RadioBrowserStationProvider::emitStationBatch(
    std::shared_ptr<std::vector<StationEntity>> const& stations,
    std::size_t nextIndex,
    std::shared_ptr<StationFetchRequestState> const& state) const {
    if (state->subscription.isCanceled()) {
        return;
    }

    std::size_t currentIndex {nextIndex};
    std::size_t processedCount {0};
    while (currentIndex < stations->size() && processedCount < STATION_EMIT_BATCH_SIZE) {
        if (state->subscription.isCanceled()) {
            return;
        }

        state->onStation(stations->at(currentIndex));
        ++currentIndex;
        ++processedCount;
    }

    if (currentIndex >= stations->size()) {
        finishRequest(state);
        return;
    }

    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        return;
    }

    QTimer::singleShot(0, application, [this, stations, currentIndex, state]() {
        emitStationBatch(stations, currentIndex, state);
    });
}

QUrl RadioBrowserStationProvider::createStationsUrl(std::size_t urlIndex) const {
    QUrl url {QString::fromUtf8(RADIO_BROWSER_API_URLS.at(urlIndex))};

    QUrlQuery query {};
    query.addQueryItem("hidebroken", "true");
    query.addQueryItem("limit", QString::number(RADIO_BROWSER_LIMIT));
    url.setQuery(query);

    return url;
}

QNetworkRequest RadioBrowserStationProvider::createNetworkRequest(QUrl const& url) const {
    QNetworkRequest request {url};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", QByteArray {RADIO_BROWSER_USER_AGENT});
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
    return request;
}

std::vector<StationEntity> RadioBrowserStationProvider::parseStations(QByteArray const& payload) const {
    std::vector<StationEntity> stations {};

    try {
        nlohmann::json const parsedJson {nlohmann::json::parse(payload.constData())};
        if (!parsedJson.is_array()) {
            LOG(ERROR) << "Unexpected radio-browser payload: expected JSON array.";
            return stations;
        }

        std::size_t skippedRecords {0};
        std::size_t invalidUuidRecords {0};
        std::size_t acceptedRecords {0};
        std::size_t visitedRecords {0};
        collectStationsFromJson(parsedJson, stations, skippedRecords, invalidUuidRecords, acceptedRecords, visitedRecords);

        LOG(INFO) << "Parsed " << acceptedRecords << " radio-browser stations from " << visitedRecords << " records.";

        if (invalidUuidRecords > 0) {
            LOG(WARNING) << "Rejected " << invalidUuidRecords << " radio-browser station records because of invalid UUIDs.";
        }

        if (skippedRecords > 0) {
            LOG(WARNING) << "Skipped " << skippedRecords << " malformed station records from radio-browser.info.";
        }
    }
    catch (std::exception const& ex) {
        LOG(ERROR) << "Failed to parse stations from radio-browser.info: " << ex.what();
    }

    return stations;
}