#ifndef TIME_ZONE_PROVIDER_IFC_H
#define TIME_ZONE_PROVIDER_IFC_H

#include <optional>
#include <string>
#include <vector>

#include "TimeZoneGroup.h"

/**
 * Provides the available time zones of the system, grouped by their behaviour,
 * so that the user does not have to choose between hundreds of identical entries.
 */
class TimeZoneProviderIfc {
public:

    virtual ~TimeZoneProviderIfc() = default;

    /**
     * Gets all available time zone groups sorted by UTC offset.
     * @return The time zone groups.
     */
    virtual std::vector<TimeZoneGroup> getTimeZoneGroups() = 0;

    /**
     * Finds the group that contains the given IANA zone identifier.
     * @param zoneId IANA zone identifier (e.g. "Europe/Zurich").
     * @return The group, or std::nullopt if the zone is unknown.
     */
    virtual std::optional<TimeZoneGroup> findGroupByZoneId(std::string const& zoneId) = 0;

    /**
     * Checks whether the given IANA zone identifier is known by the time zone database.
     * @param zoneId IANA zone identifier.
     * @return True if the zone exists.
     */
    virtual bool isValidZoneId(std::string const& zoneId) = 0;
};

#endif
