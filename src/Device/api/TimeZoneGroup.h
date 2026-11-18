#ifndef TIME_ZONE_GROUP_H
#define TIME_ZONE_GROUP_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * Represents a set of IANA time zones which currently behave identically,
 * i.e. they share the same UTC offset and the same daylight saving
 * transitions within the observed time window.
 *
 * Example: Europe/Brussels, Europe/Zurich, Europe/Berlin, ...
 */
struct TimeZoneGroup final {
    /**
     * Representative IANA zone identifier of this group (e.g. "Europe/Brussels").
     * This is the value which is meant to be persisted when the group is selected.
     */
    std::string id {};

    /**
     * Base (winter / standard) UTC offset of the group in minutes.
     */
    int32_t utcOffsetMinutes {0};

    /**
     * Formatted base offset, e.g. "UTC+01:00" or "UTC-03:30".
     */
    std::string offsetLabel {};

    /**
     * True if the zones of this group observe daylight saving time.
     */
    bool observesDst {false};

    /**
     * Human readable city names of the group, sorted alphabetically
     * (e.g. "Brussels", "Zurich", "Buenos Aires").
     */
    std::vector<std::string> cities {};

    /**
     * All IANA zone identifiers which belong to this group, sorted alphabetically.
     */
    std::vector<std::string> zoneIds {};
};

#endif
