#ifndef SRC_RADIO_INTERNAL_STATION_REPOSITORY_H
#define SRC_RADIO_INTERNAL_STATION_REPOSITORY_H

#include <Mediator.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "StationRepositoryIfc.h"

/**
 * In-memory station repository implementation.
 */
class StationRepository final : public StationRepositoryIfc {
public:

    explicit StationRepository(Mediator& mediator);
    ~StationRepository() final = default;

    /**
     * @see StationRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see StationRepositoryIfc::addStation
     */
    void addStation(StationEntity const& station) final;

    /**
     * @see StationRepositoryIfc::removeStation
     */
    void removeStation(StationId const& stationId) final;

    /**
     * @see StationRepositoryIfc::getStation
     */
    std::optional<StationEntity> getStation(StationId const& stationId) const final;

    /**
     * @see StationRepositoryIfc::getAllStations
     */
    std::vector<StationEntity> getAllStations() const final {
        return m_stations;
    }

private:

    static constexpr std::size_t INITIAL_CAPACITY {60000};

    static bool areEqual(StationEntity const& lhs, StationEntity const& rhs);
    std::string toKey(StationId const& stationId) const;

    Mediator& m_mediator;
    std::vector<StationEntity> m_stations {};
    std::unordered_map<std::string, std::size_t> m_stationIndexById {};
};

#endif // SRC_RADIO_INTERNAL_STATION_REPOSITORY_H