#include "TimeZoneProvider.h"

#include <algorithm>
#include <array>
#include <format>
#include <map>
#include <ng-log/logging.h>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace {

/**
 * Only zones within these regions are offered to the user. This skips legacy
 * aliases like "US/Eastern", "CET" or "Etc/GMT+5" and research stations
 * in Antarctica which would only clutter the list.
 */
constexpr std::array<std::string_view, 8> SELECTABLE_REGIONS {
    "Africa/", "America/", "Asia/", "Atlantic/", "Australia/", "Europe/", "Indian/", "Pacific/",
};

constexpr std::string_view UTC_ZONE_ID {"Etc/UTC"};

constexpr std::chrono::days GROUPING_WINDOW {365};

/**
 * Describes the behaviour of a zone within the grouping window:
 * a sequence of (transition time, UTC offset in seconds). The first
 * entry always has transition time 0, as it represents the offset at
 * the reference time.
 */
using ZoneBehaviour = std::vector<std::pair<int64_t, int32_t>>;

bool isSelectableZoneName(std::string_view name) {
    if (name == UTC_ZONE_ID) {
        return true;
    }
    return std::ranges::any_of(SELECTABLE_REGIONS, [name](std::string_view region) { return name.starts_with(region); });
}

ZoneBehaviour computeBehaviour(std::chrono::time_zone const& zone, std::chrono::sys_seconds referenceTime) {
    ZoneBehaviour behaviour {};
    std::chrono::sys_seconds const windowEnd {referenceTime + GROUPING_WINDOW};
    std::chrono::sys_seconds current {referenceTime};

    while (true) {
        std::chrono::sys_info const info {zone.get_info(current)};
        int32_t const offset {static_cast<int32_t>(info.offset.count())};

        // Transitions which only change the abbreviation are ignored
        if (behaviour.empty()) {
            behaviour.emplace_back(0, offset);
        }
        else if (behaviour.back().second != offset) {
            behaviour.emplace_back(info.begin.time_since_epoch().count(), offset);
        }

        if (info.end >= windowEnd || info.end <= current) {
            break;
        }
        current = info.end;
    }
    return behaviour;
}

struct GroupBuilder final {
    std::vector<std::string> canonicalZoneIds {};
    std::vector<std::string> zoneIds {};
};

} // namespace

std::vector<TimeZoneGroup> TimeZoneProvider::getTimeZoneGroups() {
    std::lock_guard const lock {m_mutex};
    refreshIfRequired();
    return m_groups;
}

std::optional<TimeZoneGroup> TimeZoneProvider::findGroupByZoneId(std::string const& zoneId) {
    std::lock_guard const lock {m_mutex};
    refreshIfRequired();

    auto const containsZone = [](TimeZoneGroup const& group, std::string const& id) {
        return std::ranges::binary_search(group.zoneIds, id);
    };

    for (TimeZoneGroup const& group : m_groups) {
        if (containsZone(group, zoneId)) {
            return group;
        }
    }

    // Zone might be a link which is not part of the selectable zones (e.g. "US/Eastern"),
    // in this case the group of the link target is used.
    try {
        std::string const target {std::chrono::locate_zone(zoneId)->name()};
        for (TimeZoneGroup const& group : m_groups) {
            if (containsZone(group, target)) {
                return group;
            }
        }
    }
    catch (std::runtime_error const&) {
        // unknown zone
    }
    return std::nullopt;
}

bool TimeZoneProvider::isValidZoneId(std::string const& zoneId) {
    try {
        return std::chrono::locate_zone(zoneId) != nullptr;
    }
    catch (std::runtime_error const&) {
        return false;
    }
}

void TimeZoneProvider::refreshIfRequired() {
    auto const now {std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now())};
    if (m_cachedAt.has_value() && (now - *m_cachedAt) < CACHE_LIFETIME) {
        return;
    }

    try {
        m_groups = buildGroups(now);
        m_cachedAt = now;
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to load time zone database: " << e.what();
        m_groups.clear();
        m_cachedAt.reset();
    }
}

std::vector<TimeZoneGroup> TimeZoneProvider::buildGroups(std::chrono::sys_seconds referenceTime) {
    std::chrono::tzdb const& tzdb {std::chrono::get_tzdb()};

    std::map<ZoneBehaviour, GroupBuilder> builders {};
    std::map<std::string_view, ZoneBehaviour const*> behaviourByZone {};

    // The number of aliases pointing to a zone is used as popularity hint to pick
    // a well known representative (e.g. Europe/Berlin instead of Africa/Ceuta).
    std::map<std::string_view, std::size_t> linkCount {};
    for (std::chrono::time_zone_link const& link : tzdb.links) {
        ++linkCount[link.target()];
    }

    for (std::chrono::time_zone const& zone : tzdb.zones) {
        if (!isSelectableZoneName(zone.name())) {
            continue;
        }
        auto [it, inserted] {builders.try_emplace(computeBehaviour(zone, referenceTime))};
        it->second.canonicalZoneIds.emplace_back(zone.name());
        it->second.zoneIds.emplace_back(zone.name());
        behaviourByZone.emplace(zone.name(), &it->first);
    }

    // Links are required as well: since tzdata 2022b many well known zones
    // (e.g. Europe/Amsterdam, Europe/Stockholm) are only links to other zones.
    for (std::chrono::time_zone_link const& link : tzdb.links) {
        if (!isSelectableZoneName(link.name())) {
            continue;
        }

        ZoneBehaviour const* behaviour {nullptr};
        if (auto const known {behaviourByZone.find(link.target())}; known != behaviourByZone.end()) {
            behaviour = known->second;
        }

        if (behaviour == nullptr) {
            // Target is not selectable itself (e.g. Etc/GMT-1), compute its behaviour
            std::chrono::time_zone const* target {tzdb.locate_zone(link.target())};
            auto [it, inserted] {builders.try_emplace(computeBehaviour(*target, referenceTime))};
            it->second.zoneIds.emplace_back(link.name());
        }
        else {
            builders.at(*behaviour).zoneIds.emplace_back(link.name());
        }
    }

    std::vector<TimeZoneGroup> groups {};
    groups.reserve(builders.size());

    for (auto& [behaviour, builder] : builders) {
        TimeZoneGroup group {};

        std::ranges::sort(builder.zoneIds);
        std::ranges::sort(builder.canonicalZoneIds);

        bool const containsUtc {std::ranges::binary_search(builder.zoneIds, UTC_ZONE_ID)};
        if (containsUtc) {
            group.id = UTC_ZONE_ID;
        }
        else if (!builder.canonicalZoneIds.empty()) {
            // max_element keeps the first (alphabetical) element on equal counts
            group.id = *std::ranges::max_element(builder.canonicalZoneIds, {}, [&linkCount](std::string const& zoneId) {
                auto const it {linkCount.find(zoneId)};
                return it == linkCount.end() ? std::size_t {0} : it->second;
            });
        }
        else {
            group.id = builder.zoneIds.front();
        }

        // The lowest offset within a year is the winter (standard) time. This is
        // also correct for zones with negative DST like Europe/Dublin.
        auto const minOffset {std::ranges::min_element(behaviour, {}, &std::pair<int64_t, int32_t>::second)};
        group.utcOffsetMinutes = minOffset->second / 60;
        group.offsetLabel = formatOffset(group.utcOffsetMinutes);
        group.observesDst = behaviour.size() > 1;

        for (std::string const& zoneId : builder.zoneIds) {
            group.cities.emplace_back(toCityName(zoneId));
        }
        std::ranges::sort(group.cities);
        auto const duplicates {std::ranges::unique(group.cities)};
        group.cities.erase(duplicates.begin(), duplicates.end());

        group.zoneIds = std::move(builder.zoneIds);
        groups.emplace_back(std::move(group));
    }

    std::ranges::sort(groups, [](TimeZoneGroup const& lhs, TimeZoneGroup const& rhs) {
        if (lhs.utcOffsetMinutes != rhs.utcOffsetMinutes) {
            return lhs.utcOffsetMinutes < rhs.utcOffsetMinutes;
        }
        return lhs.cities.front() < rhs.cities.front();
    });

    return groups;
}

std::string TimeZoneProvider::formatOffset(int32_t offsetMinutes) {
    char const sign {offsetMinutes < 0 ? '-' : '+'};
    int32_t const absolute {offsetMinutes < 0 ? -offsetMinutes : offsetMinutes};
    return std::format("UTC{}{:02}:{:02}", sign, absolute / 60, absolute % 60);
}

std::string TimeZoneProvider::toCityName(std::string const& zoneId) {
    if (zoneId == UTC_ZONE_ID) {
        return "UTC";
    }

    std::size_t const separator {zoneId.find_last_of('/')};
    std::string city {separator == std::string::npos ? zoneId : zoneId.substr(separator + 1)};
    std::ranges::replace(city, '_', ' ');
    return city;
}
