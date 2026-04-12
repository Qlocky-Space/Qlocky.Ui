#ifndef SRC_RADIO_API_STATION_SERVICE_IFC_H
#define SRC_RADIO_API_STATION_SERVICE_IFC_H

#include <memory>

#include "StationProviderIfc.h"

/**
 * Station service interface.
 *
 * The station service coordinates station searches across registered providers.
 */
class StationServiceIfc {
public:

    virtual ~StationServiceIfc() = default;

    /**
     * Register a station provider.
     * @param provider The provider to register.
     */
    virtual void registerProvider(std::shared_ptr<StationProviderIfc> provider) = 0;

    /**
     * Search stations asynchronously.
     * @param filter The station filter applied to the search.
     * @return A stream of matching stations.
     */
    virtual Stream<StationEntity> searchStations(StationFilter const& filter) = 0;
};

#endif // SRC_RADIO_API_STATION_SERVICE_IFC_H