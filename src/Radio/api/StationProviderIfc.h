#ifndef SRC_RADIO_API_STATION_PROVIDER_IFC_H
#define SRC_RADIO_API_STATION_PROVIDER_IFC_H

#include "StationEntity.h"
#include "Stream.h"

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
     * Create a stream that yields all stations from the provider asynchronously.
     * @return The asynchronous station stream.
     */
    virtual Stream<StationEntity> streamAllStations() = 0;
};

#endif // SRC_RADIO_API_STATION_PROVIDER_IFC_H