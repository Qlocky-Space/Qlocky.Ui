#include "RadioBrowserStationProvider.h"

#include <ng-log/logging.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <QCoreApplication>
#include <QMetaObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <thread>

namespace {

constexpr char const* RADIO_BROWSER_API_URL {"https://de1.api.radio-browser.info/json/stations"};
constexpr char const* RADIO_BROWSER_USER_AGENT {"Qlocky/1.0"};
constexpr int RADIO_BROWSER_LIMIT {100000};

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

} // namespace

RadioBrowserStationProvider::RadioBrowserStationProvider() :
    m_networkAccessManager {} {
}

void RadioBrowserStationProvider::streamAllStationsAsync(StationHandler onStation, FinishedHandler onFinished) {
    QUrl url {QString::fromUtf8(RADIO_BROWSER_API_URL)};
    QUrlQuery query {};
    query.addQueryItem("hidebroken", "true");
    query.addQueryItem("limit", QString::number(RADIO_BROWSER_LIMIT));
    url.setQuery(query);

    QNetworkRequest request {url};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", QByteArray {RADIO_BROWSER_USER_AGENT});

    QNetworkReply* reply {m_networkAccessManager.get(request)};
    QObject::connect(reply, &QNetworkReply::finished, [this, reply, onStation = std::move(onStation), onFinished = std::move(onFinished)]() mutable {
        std::unique_ptr<QNetworkReply, void (*)(QNetworkReply*)> replyGuard(reply, [](QNetworkReply* currentReply) {
            if (currentReply != nullptr) {
                currentReply->deleteLater();
            }
        });

        if (reply->error() != QNetworkReply::NoError) {
            LOG(ERROR) << "Failed to fetch stations from radio-browser.info: " << reply->errorString().toStdString();
            onFinished();
            return;
        }

        QByteArray const payload {reply->readAll()};
        std::thread([this, payload, onStation = std::move(onStation), onFinished = std::move(onFinished)]() mutable {
            std::vector<StationEntity> const stations {parseStations(payload)};

            QCoreApplication* application {QCoreApplication::instance()};
            if (application == nullptr) {
                return;
            }

            QMetaObject::invokeMethod(application, [onStation = std::move(onStation), onFinished = std::move(onFinished), stations]() mutable {
                for (StationEntity const& station : stations) {
                    onStation(station);
                }

                onFinished(); }, Qt::QueuedConnection);
        }).detach();
    });
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