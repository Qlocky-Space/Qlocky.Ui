#ifndef SRC_RADIO_API_STATION_REPOSITORY_IFC_H
#define SRC_RADIO_API_STATION_REPOSITORY_IFC_H

#include <optional>
#include <vector>

#include "StationEntity.h"

/**
 * Station repository interface.
 *
 * This repository stores the aggregated station collection used by the Radio module.
 */
class StationRepositoryIfc {
public:

    virtual ~StationRepositoryIfc() = default;

    /**
     * Initialize the repository.
     */
    virtual void initialize() = 0;

    /**
     * Add or update a station in the repository.
     * @param station The station profile to store.
     */
    virtual void addStation(StationEntity const& station) = 0;

    /**
     * Remove a station from the repository.
     * @param stationId The station identifier to remove.
     */
    virtual void removeStation(StationId const& stationId) = 0;

    /**
     * Retrieve a station by identifier.
     * @param stationId The station identifier to look up.
     * @return The matching station profile, if found.
     */
    virtual std::optional<StationEntity> getStation(StationId const& stationId) const = 0;

    /**
     * Retrieve all stations in the repository.
     * @return A list of all stored stations.
     */
    virtual std::vector<StationEntity> getAllStations() const = 0;
};

#endif // SRC_RADIO_API_STATION_REPOSITORY_IFC_H