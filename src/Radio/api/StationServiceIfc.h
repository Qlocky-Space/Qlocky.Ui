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
      * Start updating stations from all registered providers asynchronously.
      * @param filter The station filter applied to the update.
     */
    virtual void updateStations(StationFilter const& filter = {}) = 0;

    /**
     * Cancel the active asynchronous station update.
     */
    virtual void cancel() = 0;
};

#endif // SRC_RADIO_API_STATION_SERVICE_IFC_H