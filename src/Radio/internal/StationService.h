#ifndef SRC_RADIO_INTERNAL_STATION_SERVICE_H
#define SRC_RADIO_INTERNAL_STATION_SERVICE_H

#include <cstdint>
#include <memory>
#include <unordered_set>
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
     * @see StationServiceIfc::registerProvider
     */
    void registerProvider(std::shared_ptr<StationProviderIfc> provider) final;

    /**
     * @see StationServiceIfc::collectStations
     */
    void collectStations() final;

private:

    struct ActiveCollectionState;
    struct PendingStationChanges;

    void onProviderStation(
        std::shared_ptr<ActiveCollectionState> collectionState,
        std::uint64_t collectionGeneration,
        StationEntity const& station);
    void onProviderFinished(
        std::shared_ptr<ActiveCollectionState> collectionState,
        std::uint64_t collectionGeneration);
    void finalizeCollection(
        std::shared_ptr<ActiveCollectionState> collectionState,
        std::uint64_t collectionGeneration);
    void applyPendingChanges(
        std::shared_ptr<PendingStationChanges> pendingChanges,
        std::uint64_t collectionGeneration);

    StationRepositoryIfc& m_repository;
    std::vector<std::shared_ptr<StationProviderIfc>> m_providers;
    std::uint64_t m_collectionGeneration {0};
};

#endif // SRC_RADIO_INTERNAL_STATION_SERVICE_H