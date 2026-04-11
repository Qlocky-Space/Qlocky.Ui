#ifndef SRC_RADIO_API_STATION_SERVICE_IFC_H
#define SRC_RADIO_API_STATION_SERVICE_IFC_H

#include <memory>

#include "StationProviderIfc.h"

/**
 * Station service interface.
 *
 * The station service aggregates stations from registered providers and stores
 * the resulting collection in the repository.
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
     * Collect stations from all registered providers asynchronously.
     */
    virtual void collectStations() = 0;
};

#endif // SRC_RADIO_API_STATION_SERVICE_IFC_H