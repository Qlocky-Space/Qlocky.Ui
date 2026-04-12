#ifndef SRC_RADIO_INTERNAL_STATION_SERVICE_H
#define SRC_RADIO_INTERNAL_STATION_SERVICE_H

#include <memory>
#include <unordered_set>
#include <vector>

#include "StationProviderIfc.h"
#include "StationServiceIfc.h"

/**
 * Station service implementation.
 */
class StationService final : public StationServiceIfc {
public:

    StationService() = default;
    ~StationService() final = default;

    /**
     * @see StationServiceIfc::registerProvider
     */
    void registerProvider(std::shared_ptr<StationProviderIfc> provider) final;

    /**
     * @see StationServiceIfc::searchStations
     */
    Stream<StationEntity> searchStations(StationFilter const& filter) final;

private:

    std::vector<std::shared_ptr<StationProviderIfc>> m_providers;
};

#endif // SRC_RADIO_INTERNAL_STATION_SERVICE_H