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
     * @see StationProviderIfc::getAllStations
     */
    std::vector<StationProfile> getAllStations() final;

private:

    std::vector<StationProfile> parseStations(QByteArray const& payload) const;

    QNetworkAccessManager m_networkAccessManager;
};

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H