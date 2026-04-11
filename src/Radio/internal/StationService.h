#ifndef SRC_RADIO_INTERNAL_STATION_SERVICE_H
#define SRC_RADIO_INTERNAL_STATION_SERVICE_H

#include <Mediator.h>
#include <memory>
#include <unordered_set>
#include <vector>

#include "events/StationServiceStateChangedEvent.h"
#include "StationProviderIfc.h"
#include "StationRepositoryIfc.h"
#include "StationServiceIfc.h"

/**
 * Station service implementation.
 */
class StationService final : public StationServiceIfc {
public:

    StationService(StationRepositoryIfc& repository, Mediator& mediator);
    ~StationService() final = default;

    /**
     * @see StationServiceIfc::registerProvider
     */
    void registerProvider(std::shared_ptr<StationProviderIfc> provider) final;

    /**
     * @see StationServiceIfc::updateStationsAsync
     */
    void updateStationsAsync() final;

    /**
     * @see StationServiceIfc::cancel
     */
    void cancel() final;

private:

    void onProviderStation(
        std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds,
        StationEntity const& station);
    void onProviderFinished(
        std::shared_ptr<std::vector<StationId>> const& existingStationIds,
        std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds,
        std::shared_ptr<std::size_t> const& pendingProviders);
    void finalizeCollection(
        std::shared_ptr<std::vector<StationId>> const& existingStationIds,
        std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds);
    void notifyStateChanged(StationServiceStateChangedEvent::State state) const;

    StationRepositoryIfc& m_repository;
    Mediator& m_mediator;
    std::vector<std::shared_ptr<StationProviderIfc>> m_providers;
    std::vector<Stream<StationEntity>::Subscription> m_activeSubscriptions;
};

#endif // SRC_RADIO_INTERNAL_STATION_SERVICE_H