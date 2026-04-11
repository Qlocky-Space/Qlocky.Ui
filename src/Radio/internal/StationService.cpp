#include "StationService.h"

#include <algorithm>
#include <QCoreApplication>
#include <QMetaObject>
#include <QTimer>

constexpr std::size_t APPLY_BATCH_SIZE {250};

struct StationService::ActiveCollectionState {
    std::vector<StationId> existingStationIds {};
    std::unordered_set<std::string> seenStationIds {};
    std::size_t pendingProviders {0};
};

struct StationService::PendingStationChanges {
    std::vector<StationEntity> additions {};
    std::vector<StationId> removals {};
    std::size_t nextAdditionIndex {0};
    std::size_t nextRemovalIndex {0};
};

StationService::StationService(StationRepositoryIfc& repository) :
    m_repository {repository} {
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

void StationService::collectStations() {
    std::uint64_t const collectionGeneration {++m_collectionGeneration};

    auto collectionState = std::make_shared<ActiveCollectionState>();
    for (StationEntity const& station : m_repository.getAllStations()) {
        collectionState->existingStationIds.push_back(station.id);
    }

    if (m_providers.empty()) {
        finalizeCollection(collectionState, collectionGeneration);
        return;
    }

    collectionState->pendingProviders = m_providers.size();

    for (std::shared_ptr<StationProviderIfc> const& provider : m_providers) {
        provider->streamAllStationsAsync(
            [this, collectionState, collectionGeneration](StationEntity const& station) {
                QCoreApplication* application {QCoreApplication::instance()};
                if (application == nullptr) {
                    return;
                }

                QMetaObject::invokeMethod(application, [this, collectionState, collectionGeneration, station]() { onProviderStation(collectionState, collectionGeneration, station); }, Qt::QueuedConnection);
            },
            [this, collectionState, collectionGeneration]() {
                QCoreApplication* application {QCoreApplication::instance()};
                if (application == nullptr) {
                    return;
                }

                QMetaObject::invokeMethod(application, [this, collectionState, collectionGeneration]() { onProviderFinished(collectionState, collectionGeneration); }, Qt::QueuedConnection);
            });
    }
}

void StationService::onProviderStation(
    std::shared_ptr<ActiveCollectionState> collectionState,
    std::uint64_t collectionGeneration,
    StationEntity const& station) {
    if (collectionGeneration != m_collectionGeneration) {
        return;
    }

    if (!station.id.isValid()) {
        return;
    }

    collectionState->seenStationIds.insert(station.id.toString());
    m_repository.addStation(station);
}

void StationService::onProviderFinished(
    std::shared_ptr<ActiveCollectionState> collectionState,
    std::uint64_t collectionGeneration) {
    if (collectionGeneration != m_collectionGeneration) {
        return;
    }

    if (collectionState->pendingProviders == 0) {
        return;
    }

    --collectionState->pendingProviders;
    if (collectionState->pendingProviders == 0) {
        finalizeCollection(collectionState, collectionGeneration);
    }
}

void StationService::finalizeCollection(
    std::shared_ptr<ActiveCollectionState> collectionState,
    std::uint64_t collectionGeneration) {
    if (collectionGeneration != m_collectionGeneration) {
        return;
    }

    auto pendingChanges = std::make_shared<PendingStationChanges>();

    for (StationId const& stationId : collectionState->existingStationIds) {
        if (collectionState->seenStationIds.count(stationId.toString()) == 0) {
            pendingChanges->removals.push_back(stationId);
        }
    }

    if (pendingChanges->removals.empty()) {
        return;
    }

    applyPendingChanges(pendingChanges, collectionGeneration);
}

void StationService::applyPendingChanges(
    std::shared_ptr<PendingStationChanges> pendingChanges,
    std::uint64_t collectionGeneration) {
    if (collectionGeneration != m_collectionGeneration) {
        return;
    }

    std::size_t processedCount {0};
    while (pendingChanges->nextAdditionIndex < pendingChanges->additions.size() && processedCount < APPLY_BATCH_SIZE) {
        m_repository.addStation(pendingChanges->additions.at(pendingChanges->nextAdditionIndex));
        ++pendingChanges->nextAdditionIndex;
        ++processedCount;
    }

    while (pendingChanges->nextAdditionIndex >= pendingChanges->additions.size() && pendingChanges->nextRemovalIndex < pendingChanges->removals.size() && processedCount < APPLY_BATCH_SIZE) {
        m_repository.removeStation(pendingChanges->removals.at(pendingChanges->nextRemovalIndex));
        ++pendingChanges->nextRemovalIndex;
        ++processedCount;
    }

    bool const hasMoreAdditions {pendingChanges->nextAdditionIndex < pendingChanges->additions.size()};
    bool const hasMoreRemovals {pendingChanges->nextRemovalIndex < pendingChanges->removals.size()};
    if (!hasMoreAdditions && !hasMoreRemovals) {
        return;
    }

    QCoreApplication* application {QCoreApplication::instance()};
    if (application == nullptr) {
        return;
    }

    QTimer::singleShot(0, application, [this, pendingChanges, collectionGeneration]() mutable {
        applyPendingChanges(pendingChanges, collectionGeneration);
    });
}