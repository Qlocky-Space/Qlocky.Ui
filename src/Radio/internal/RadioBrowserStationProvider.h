#ifndef SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H
#define SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H

#include <memory>
#include <RestApi.h>

#include "RadioBrowserAPIv1.h"
#include "StationProviderIfc.h"

/**
 * Station provider backed by the radio-browser.info API.
 */
class RadioBrowserStationProvider final : public StationProviderIfc {
public:

    explicit RadioBrowserStationProvider(RestApi& restApi);
    ~RadioBrowserStationProvider() final = default;

    /**
        * @see StationProviderIfc::streamAllStations
     */
    Stream<StationEntity> streamAllStations() final;

private:

    void handleStationsResponse(
        Result<RadioBrowserAPIv1, RestApiCode> const& result,
        Stream<StationEntity>::Observer const& observer);
    void emitStations(
        std::vector<StationEntity> stations,
        Stream<StationEntity>::Observer const& observer) const;
    void emitStationBatch(
        std::shared_ptr<std::vector<StationEntity>> const& stations,
        std::size_t nextIndex,
        Stream<StationEntity>::Observer const& observer) const;
    std::string createStationsUrl() const;

    RestApi& m_restApi;
};

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_STATION_PROVIDER_H