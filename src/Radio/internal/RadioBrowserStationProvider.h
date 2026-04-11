#ifndef SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H
#define SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H

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
        * @see StationProviderIfc::streamAllStationsAsync
     */
    void streamAllStationsAsync(StationHandler onStation, FinishedHandler onFinished) final;

private:

    std::vector<StationEntity> parseStations(QByteArray const& payload) const;

    QNetworkAccessManager m_networkAccessManager;
};

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H