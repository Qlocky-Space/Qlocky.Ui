#include "StationRepository.h"

#include <algorithm>

#include "events/StationAddedEvent.h"
#include "events/StationRemovedEvent.h"
#include "events/StationUpdatedEvent.h"

StationRepository::StationRepository(Mediator& mediator) :
    m_mediator {mediator} {
}

void StationRepository::initialize() {
    m_stations.clear();
}

void StationRepository::addStation(StationEntity const& station) {
    auto it = std::find_if(m_stations.begin(), m_stations.end(), [&station](StationEntity const& current) {
        return current.id == station.id;
    });

    if (it == m_stations.end()) {
        m_stations.push_back(station);
        m_mediator.notify(StationAddedEvent {station});
        return;
    }

    if (!areEqual(*it, station)) {
        *it = station;
        m_mediator.notify(StationUpdatedEvent {station});
    }
}

void StationRepository::removeStation(StationId const& stationId) {
    auto it = std::find_if(m_stations.begin(), m_stations.end(), [&stationId](StationEntity const& station) {
        return station.id == stationId;
    });
    if (it == m_stations.end()) {
        return;
    }

    m_stations.erase(it);
    m_mediator.notify(StationRemovedEvent {stationId});
}

std::optional<StationEntity> StationRepository::getStation(StationId const& stationId) const {
    auto it = std::find_if(m_stations.begin(), m_stations.end(), [&stationId](StationEntity const& station) {
        return station.id == stationId;
    });

    if (it == m_stations.end()) {
        return std::nullopt;
    }

    return *it;
}

bool StationRepository::areEqual(StationEntity const& lhs, StationEntity const& rhs) {
    return lhs.id == rhs.id;
}