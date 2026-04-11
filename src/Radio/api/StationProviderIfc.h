#ifndef SRC_RADIO_API_STATION_PROVIDER_IFC_H
#define SRC_RADIO_API_STATION_PROVIDER_IFC_H

#include <functional>

#include "StationEntity.h"

/**
 * Station provider interface.
 *
 * A provider supplies stations from one source, for example a remote API
 * or a static catalog.
 */
class StationProviderIfc {
public:

    using StationHandler = std::function<void(StationEntity const&)>;
    using FinishedHandler = std::function<void()>;

    virtual ~StationProviderIfc() = default;

    /**
     * Stream stations from the provider asynchronously.
     * @param onStation Callback invoked for each station.
     * @param onFinished Callback invoked after the stream has completed.
     */
    virtual void streamAllStationsAsync(StationHandler onStation, FinishedHandler onFinished) = 0;
};

#endif // SRC_RADIO_API_STATION_PROVIDER_IFC_H