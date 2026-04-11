#ifndef SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H
#define SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H

#include <memory>
#include <QNetworkAccessManager>

#include "StationProviderIfc.h"

/**
 * Station provider backed by the radio-browser.info API.
 */
class RadioBrowserStationProvider final : public StationProviderIfc {
public:

    RadioBrowserStationProvider();
    ~RadioBrowserStationProvider() final = default;

    /**
        * @see StationProviderIfc::streamAllStations
     */
    Stream<StationEntity> streamAllStations() final;

private:

    struct StationFetchRequestState;

    std::shared_ptr<StationFetchRequestState> createRequestState(
        Stream<StationEntity>::ItemHandler onStation,
        Stream<StationEntity>::FinishedHandler onFinished,
        Stream<StationEntity>::Subscription const& subscription) const;
    void startNextRequest(std::shared_ptr<StationFetchRequestState> const& state);
    void finishRequest(std::shared_ptr<StationFetchRequestState> const& state) const;
    void handleReplyFinished(QNetworkReply* reply, std::shared_ptr<StationFetchRequestState> const& state);
    void parseAndEmitStations(QByteArray payload, std::shared_ptr<StationFetchRequestState> const& state) const;
    void emitStations(std::vector<StationEntity> stations, std::shared_ptr<StationFetchRequestState> const& state) const;
    void emitStationBatch(
        std::shared_ptr<std::vector<StationEntity>> const& stations,
        std::size_t nextIndex,
        std::shared_ptr<StationFetchRequestState> const& state) const;
    QUrl createStationsUrl(std::size_t urlIndex) const;
    QNetworkRequest createNetworkRequest(QUrl const& url) const;

    std::vector<StationEntity> parseStations(QByteArray const& payload) const;

    QNetworkAccessManager m_networkAccessManager;
};

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H