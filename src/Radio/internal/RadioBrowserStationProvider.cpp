#include "RadioBrowserStationProvider.h"

#include <ng-log/logging.h>
#include <nlohmann/json.hpp>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

namespace {

constexpr char const* RADIO_BROWSER_API_URL {"https://de1.api.radio-browser.info/json/stations"};
constexpr char const* RADIO_BROWSER_USER_AGENT {"Qlocky/1.0"};
constexpr int RADIO_BROWSER_LIMIT {100};

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

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
        RadioBrowserStationRecord,
        stationuuid,
        name,
        url,
        url_resolved,
        favicon,
        tags,
        language,
        countrycode,
        votes)
};

StationProfile toStationProfile(RadioBrowserStationRecord const& record) {
    std::string const streamUrl {record.url_resolved.empty() ? record.url : record.url_resolved};

    return StationProfile {
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

} // namespace

RadioBrowserStationProvider::RadioBrowserStationProvider() :
    m_networkAccessManager {} {
}

std::vector<StationProfile> RadioBrowserStationProvider::getAllStations() {
    QUrl url {QString::fromUtf8(RADIO_BROWSER_API_URL)};
    QUrlQuery query {};
    query.addQueryItem("hidebroken", "true");
    query.addQueryItem("limit", QString::number(RADIO_BROWSER_LIMIT));
    url.setQuery(query);

    QNetworkRequest request {url};
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", QByteArray {RADIO_BROWSER_USER_AGENT});

    QNetworkReply* reply {m_networkAccessManager.get(request)};
    QEventLoop eventLoop {};
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    std::unique_ptr<QNetworkReply, void (*)(QNetworkReply*)> replyGuard(reply, [](QNetworkReply* currentReply) {
        if (currentReply != nullptr) {
            currentReply->deleteLater();
        }
    });

    if (reply->error() != QNetworkReply::NoError) {
        LOG(ERROR) << "Failed to fetch stations from radio-browser.info: " << reply->errorString().toStdString();
        return {};
    }

    return parseStations(reply->readAll());
}

std::vector<StationProfile> RadioBrowserStationProvider::parseStations(QByteArray const& payload) const {
    std::vector<StationProfile> stations {};

    try {
        std::vector<RadioBrowserStationRecord> const records {
            nlohmann::json::parse(payload.constData()).get<std::vector<RadioBrowserStationRecord>>()};

        stations.reserve(records.size());
        for (RadioBrowserStationRecord const& record : records) {
            StationProfile const station {toStationProfile(record)};
            if (!station.StationId.isValid()) {
                continue;
            }

            stations.push_back(station);
        }
    }
    catch (std::exception const& ex) {
        LOG(ERROR) << "Failed to parse stations from radio-browser.info: " << ex.what();
    }

    return stations;
}