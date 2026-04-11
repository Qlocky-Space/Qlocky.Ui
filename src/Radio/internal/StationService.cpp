#include "StationService.h"

#include <algorithm>
#include <unordered_map>

#include "StationMapper.h"

StationService::StationService(StationRepositoryIfc& repository) :
    m_repository {repository} {
}

void StationService::initialize() {
    m_isInitialized = true;
    collectStations();
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

    if (m_isInitialized) {
        collectStations();
    }
}

void StationService::collectStations() {
    std::unordered_map<std::string, StationProfile> aggregatedStations;

    for (std::shared_ptr<StationProviderIfc> const& provider : m_providers) {
        for (StationProfile const& station : provider->getAllStations()) {
            if (!station.StationId.isValid()) {
                continue;
            }

            aggregatedStations[station.StationId.toString()] = station;
        }
    }

    std::vector<StationEntity> const existingStations {m_repository.getAllStations()};

    for (auto const& [stationId, station] : aggregatedStations) {
        m_repository.addStation(StationMapper::toEntity(station));
    }

    for (StationEntity const& station : existingStations) {
        if (aggregatedStations.count(station.id.toString()) == 0) {
            m_repository.removeStation(station.id);
        }
    }
}