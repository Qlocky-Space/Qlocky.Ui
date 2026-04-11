#ifndef SRC_RADIO_API_STATION_PROVIDER_IFC_H
#define SRC_RADIO_API_STATION_PROVIDER_IFC_H

#include <vector>

#include "StationProfile.h"

/**
 * Station provider interface.
 *
 * A provider supplies stations from one source, for example a remote API
 * or a static catalog.
 */
class StationProviderIfc {
public:

    virtual ~StationProviderIfc() = default;

    /**
     * Retrieve all stations from the provider.
     * @return A list of stations exposed by the provider.
     */
    virtual std::vector<StationProfile> getAllStations() = 0;
};

#endif // SRC_RADIO_API_STATION_PROVIDER_IFC_H