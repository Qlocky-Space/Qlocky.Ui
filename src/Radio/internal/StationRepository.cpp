#include "StationRepository.h"

#include "events/StationAddedEvent.h"
#include "events/StationRemovedEvent.h"
#include "events/StationUpdatedEvent.h"

StationRepository::StationRepository(Mediator& mediator) :
    m_mediator {mediator} {
    m_stations.reserve(INITIAL_CAPACITY);
    m_stationIndexById.reserve(INITIAL_CAPACITY);
}

void StationRepository::initialize() {
    m_stations.clear();
    m_stationIndexById.clear();
}

void StationRepository::addStation(StationEntity const& station) {
    std::string const stationKey {toKey(station.id)};
    auto const it = m_stationIndexById.find(stationKey);

    if (it == m_stationIndexById.end()) {
        m_stationIndexById.emplace(stationKey, m_stations.size());
        m_stations.push_back(station);
        m_mediator.notify(StationAddedEvent {station});
        return;
    }

    StationEntity& currentStation {m_stations.at(it->second)};
    if (!areEqual(currentStation, station)) {
        currentStation = station;
        m_mediator.notify(StationUpdatedEvent {station});
    }
}

void StationRepository::removeStation(StationId const& stationId) {
    std::string const stationKey {toKey(stationId)};
    auto const it = m_stationIndexById.find(stationKey);
    if (it == m_stationIndexById.end()) {
        return;
    }

    std::size_t const removedIndex {it->second};
    std::size_t const lastIndex {m_stations.size() - 1};
    if (removedIndex != lastIndex) {
        StationEntity& movedStation {m_stations.at(lastIndex)};
        m_stations.at(removedIndex) = std::move(movedStation);
        m_stationIndexById[toKey(m_stations.at(removedIndex).id)] = removedIndex;
    }

    m_stations.pop_back();
    m_stationIndexById.erase(it);
    m_mediator.notify(StationRemovedEvent {stationId});
}

std::optional<StationEntity> StationRepository::getStation(StationId const& stationId) const {
    auto const it = m_stationIndexById.find(toKey(stationId));
    if (it == m_stationIndexById.end()) {
        return std::nullopt;
    }

    return m_stations.at(it->second);
}

bool StationRepository::areEqual(StationEntity const& lhs, StationEntity const& rhs) {
    return lhs.id == rhs.id;
}

std::string StationRepository::toKey(StationId const& stationId) const {
    return stationId.toString();
}