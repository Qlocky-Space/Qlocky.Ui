#include "StationService.h"

#include <algorithm>
#include <ng-log/logging.h>

StationService::StationService(StationRepositoryIfc& repository, Mediator& mediator) :
    m_repository {repository},
    m_mediator {mediator} {
}

void StationService::registerProvider(std::shared_ptr<StationProviderIfc> provider) {
    if (!provider) {
        return;
    }

    auto it = std::find_if(m_providers.begin(), m_providers.end(), [&provider](auto const& currentProvider) {
        return currentProvider.get() == provider.get();
    });
    if (it == m_providers.end()) {
        m_providers.push_back(std::move(provider));
    }
}

void StationService::updateStationsAsync() {
    bool const hadActiveSubscriptions {!m_activeSubscriptions.empty()};
    if (hadActiveSubscriptions) {
        LOG(WARNING) << "Station update already in progress, restarting.";
        return;
    }

    notifyStateChanged(StationServiceStateChangedEvent::State::Updating);

    auto existingStationIds = std::make_shared<std::vector<StationId>>();
    for (StationEntity const& station : m_repository.getAllStations()) {
        existingStationIds->push_back(station.id);
    }

    auto seenStationIds = std::make_shared<std::unordered_set<std::string>>();

    if (m_providers.empty()) {
        finalizeCollection(existingStationIds, seenStationIds);
        return;
    }

    auto pendingProviders = std::make_shared<std::size_t>(m_providers.size());
    m_activeSubscriptions.reserve(m_providers.size());

    for (std::shared_ptr<StationProviderIfc> const& provider : m_providers) {
        m_activeSubscriptions.push_back(provider->streamAllStations().consume(
            [this, seenStationIds](StationEntity const& station) {
                onProviderStation(seenStationIds, station);
            },
            [this, existingStationIds, seenStationIds, pendingProviders]() {
                onProviderFinished(existingStationIds, seenStationIds, pendingProviders);
            }));
    }
}

void StationService::cancel() {
    bool const hadActiveSubscriptions {!m_activeSubscriptions.empty()};
    for (Stream<StationEntity>::Subscription const& subscription : m_activeSubscriptions) {
        subscription.cancel();
    }
    m_activeSubscriptions.clear();

    if (hadActiveSubscriptions) {
        notifyStateChanged(StationServiceStateChangedEvent::State::Canceled);
    }
}

void StationService::onProviderStation(
    std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds,
    StationEntity const& station) {
    if (!station.id.isValid()) {
        return;
    }

    seenStationIds->insert(station.id.toString());
    m_repository.addStation(station);
}

void StationService::onProviderFinished(
    std::shared_ptr<std::vector<StationId>> const& existingStationIds,
    std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds,
    std::shared_ptr<std::size_t> const& pendingProviders) {
    if (*pendingProviders == 0) {
        return;
    }

    --(*pendingProviders);
    if (*pendingProviders == 0) {
        m_activeSubscriptions.clear();
        finalizeCollection(existingStationIds, seenStationIds);
    }
}

void StationService::finalizeCollection(
    std::shared_ptr<std::vector<StationId>> const& existingStationIds,
    std::shared_ptr<std::unordered_set<std::string>> const& seenStationIds) {
    for (StationId const& stationId : *existingStationIds) {
        if (seenStationIds->count(stationId.toString()) == 0) {
            m_repository.removeStation(stationId);
        }
    }

    notifyStateChanged(StationServiceStateChangedEvent::State::Finished);
}

void StationService::notifyStateChanged(StationServiceStateChangedEvent::State state) const {
    m_mediator.notify(StationServiceStateChangedEvent {state});
}