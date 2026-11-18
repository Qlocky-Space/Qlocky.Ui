#ifndef TIME_ZONE_PROVIDER_H
#define TIME_ZONE_PROVIDER_H

#include <chrono>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "TimeZoneProviderIfc.h"

/**
 * Implementation of TimeZoneProviderIfc based on the C++20 time zone
 * database (std::chrono::tzdb). It has no Qt dependencies.
 *
 * Zones are grouped when they have the same UTC offset and the same
 * daylight saving transitions within one year from a reference time.
 * This keeps e.g. Europe/Zurich and Africa/Lagos (both UTC+01:00 in winter,
 * but Lagos has no DST) in separate groups, while Europe/Zurich and
 * Europe/Brussels end up in the same one.
 *
 * @see TimeZoneProviderIfc
 */
class TimeZoneProvider : public TimeZoneProviderIfc {
public:

    TimeZoneProvider() = default;
    ~TimeZoneProvider() override = default;

    /**
     * @see TimeZoneProviderIfc::getTimeZoneGroups
     */
    std::vector<TimeZoneGroup> getTimeZoneGroups() final;

    /**
     * @see TimeZoneProviderIfc::findGroupByZoneId
     */
    std::optional<TimeZoneGroup> findGroupByZoneId(std::string const& zoneId) final;

    /**
     * @see TimeZoneProviderIfc::isValidZoneId
     */
    bool isValidZoneId(std::string const& zoneId) final;

    /**
     * Builds the time zone groups based on the given reference time.
     * Exposed for testability, the result is deterministic for a given
     * reference time and time zone database version.
     * @param referenceTime Start of the one year window used for grouping.
     * @return Groups sorted by UTC offset and city name.
     */
    static std::vector<TimeZoneGroup> buildGroups(std::chrono::sys_seconds referenceTime);

    /**
     * Formats an UTC offset as "UTC+hh:mm" / "UTC-hh:mm".
     * @param offsetMinutes Offset in minutes.
     * @return Formatted offset.
     */
    static std::string formatOffset(int32_t offsetMinutes);

    /**
     * Converts an IANA zone identifier into a human readable city name,
     * e.g. "America/Argentina/Buenos_Aires" -> "Buenos Aires".
     * @param zoneId IANA zone identifier.
     * @return City name.
     */
    static std::string toCityName(std::string const& zoneId);

private:

    /**
     * Groups are refreshed after this period, because DST transitions
     * move the grouping window over time.
     */
    static constexpr std::chrono::hours CACHE_LIFETIME {24};

    /**
     * Rebuilds the cached groups if they are outdated. Must be called with m_mutex held.
     */
    void refreshIfRequired();

    std::mutex m_mutex {};
    std::vector<TimeZoneGroup> m_groups {};
    std::optional<std::chrono::sys_seconds> m_cachedAt {};
};

#endif
