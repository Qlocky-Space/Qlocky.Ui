#ifndef SRC_RADIO_INTERNAL_STATION_SERVICE_H
#define SRC_RADIO_INTERNAL_STATION_SERVICE_H

#include <memory>
#include <vector>

#include "StationProviderIfc.h"
#include "StationRepositoryIfc.h"
#include "StationServiceIfc.h"

/**
 * Station service implementation.
 */
class StationService final : public StationServiceIfc {
public:

    explicit StationService(StationRepositoryIfc& repository);
    ~StationService() final = default;

    /**
     * @see StationServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see StationServiceIfc::registerProvider
     */
    void registerProvider(std::shared_ptr<StationProviderIfc> provider) final;

    /**
     * @see StationServiceIfc::collectStations
     */
    void collectStations() final;

private:

    StationRepositoryIfc& m_repository;
    std::vector<std::shared_ptr<StationProviderIfc>> m_providers;
    bool m_isInitialized {false};
};

#endif // SRC_RADIO_INTERNAL_STATION_SERVICE_H