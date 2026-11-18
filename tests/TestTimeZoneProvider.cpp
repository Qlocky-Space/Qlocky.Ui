#include <algorithm>
#include <chrono>
#include <gmock/gmock.h>

#include "internal/TimeZoneProvider.h"

using namespace ::testing;

namespace {

// Fixed reference time, so the grouping is deterministic (winter in the northern hemisphere)
std::chrono::sys_seconds const REFERENCE_TIME {std::chrono::sys_days {std::chrono::year {2026} / 11 / 18}};

std::vector<TimeZoneGroup> const& groups() {
    static std::vector<TimeZoneGroup> const result {TimeZoneProvider::buildGroups(REFERENCE_TIME)};
    return result;
}

TimeZoneGroup const* findGroup(std::string const& zoneId) {
    for (TimeZoneGroup const& group : groups()) {
        if (std::ranges::find(group.zoneIds, zoneId) != group.zoneIds.end()) {
            return &group;
        }
    }
    return nullptr;
}

} // namespace

TEST(TimeZoneProvider, formatOffset) {
    EXPECT_EQ(TimeZoneProvider::formatOffset(0), "UTC+00:00");
    EXPECT_EQ(TimeZoneProvider::formatOffset(60), "UTC+01:00");
    EXPECT_EQ(TimeZoneProvider::formatOffset(345), "UTC+05:45");
    EXPECT_EQ(TimeZoneProvider::formatOffset(-210), "UTC-03:30");
}

TEST(TimeZoneProvider, toCityName) {
    EXPECT_EQ(TimeZoneProvider::toCityName("Europe/Zurich"), "Zurich");
    EXPECT_EQ(TimeZoneProvider::toCityName("America/Argentina/Buenos_Aires"), "Buenos Aires");
    EXPECT_EQ(TimeZoneProvider::toCityName("Etc/UTC"), "UTC");
}

TEST(TimeZoneProvider, groupsZonesWithIdenticalRules) {
    TimeZoneGroup const* zurich {findGroup("Europe/Zurich")};
    ASSERT_NE(zurich, nullptr);

    EXPECT_EQ(zurich, findGroup("Europe/Brussels"));
    EXPECT_EQ(zurich, findGroup("Europe/Berlin"));
    EXPECT_EQ(zurich, findGroup("Europe/Paris"));
    // Link since tzdata 2022b, must be listed nevertheless
    EXPECT_EQ(zurich, findGroup("Europe/Amsterdam"));

    EXPECT_EQ(zurich->utcOffsetMinutes, 60);
    EXPECT_EQ(zurich->offsetLabel, "UTC+01:00");
    EXPECT_TRUE(zurich->observesDst);
    EXPECT_THAT(zurich->cities, IsSupersetOf({"Brussels", "Zurich", "Amsterdam"}));
}

TEST(TimeZoneProvider, separatesSameOffsetWithDifferentDst) {
    TimeZoneGroup const* zurich {findGroup("Europe/Zurich")};
    TimeZoneGroup const* lagos {findGroup("Africa/Lagos")};
    ASSERT_NE(zurich, nullptr);
    ASSERT_NE(lagos, nullptr);

    EXPECT_NE(zurich, lagos);
    EXPECT_EQ(lagos->utcOffsetMinutes, 60);
    EXPECT_FALSE(lagos->observesDst);
}

TEST(TimeZoneProvider, separatesDifferentDstTransitions) {
    // Both UTC-05:00 in winter, Bogota has no DST
    EXPECT_NE(findGroup("America/New_York"), findGroup("America/Bogota"));
    // London and Dublin behave identically (Dublin uses negative DST in tzdata)
    EXPECT_EQ(findGroup("Europe/London"), findGroup("Europe/Dublin"));
    EXPECT_EQ(findGroup("Europe/London")->utcOffsetMinutes, 0);
}

TEST(TimeZoneProvider, usesStandardOffsetInSouthernHemisphere) {
    // Sydney observes DST during the reference time, the base offset is still +10:00
    TimeZoneGroup const* sydney {findGroup("Australia/Sydney")};
    ASSERT_NE(sydney, nullptr);
    EXPECT_EQ(sydney->utcOffsetMinutes, 600);
}

TEST(TimeZoneProvider, containsUtc) {
    TimeZoneGroup const* utc {findGroup("Etc/UTC")};
    ASSERT_NE(utc, nullptr);
    EXPECT_EQ(utc->id, "Etc/UTC");
    EXPECT_EQ(utc->utcOffsetMinutes, 0);
}

TEST(TimeZoneProvider, excludesLegacyAliases) {
    EXPECT_EQ(findGroup("US/Eastern"), nullptr);
    EXPECT_EQ(findGroup("CET"), nullptr);
    EXPECT_EQ(findGroup("Etc/GMT+5"), nullptr);
}

TEST(TimeZoneProvider, groupsAreSortedAndConsistent) {
    ASSERT_FALSE(groups().empty());

    for (std::size_t i {1}; i < groups().size(); ++i) {
        EXPECT_LE(groups()[i - 1].utcOffsetMinutes, groups()[i].utcOffsetMinutes);
    }

    for (TimeZoneGroup const& group : groups()) {
        EXPECT_FALSE(group.cities.empty());
        EXPECT_TRUE(std::ranges::is_sorted(group.zoneIds));
        EXPECT_TRUE(std::ranges::binary_search(group.zoneIds, group.id)) << group.id;
    }
}

TEST(TimeZoneProvider, findGroupByZoneId) {
    TimeZoneProvider testObject {};

    auto const zurich {testObject.findGroupByZoneId("Europe/Zurich")};
    ASSERT_TRUE(zurich.has_value());
    EXPECT_THAT(zurich->zoneIds, Contains("Europe/Brussels"));

    // Legacy link resolves to the group of its target
    auto const usEastern {testObject.findGroupByZoneId("US/Eastern")};
    ASSERT_TRUE(usEastern.has_value());
    EXPECT_THAT(usEastern->zoneIds, Contains("America/New_York"));

    EXPECT_FALSE(testObject.findGroupByZoneId("Invalid/Zone").has_value());
}

TEST(TimeZoneProvider, isValidZoneId) {
    TimeZoneProvider testObject {};
    EXPECT_TRUE(testObject.isValidZoneId("Europe/Zurich"));
    EXPECT_FALSE(testObject.isValidZoneId("UTC+02:00"));
}
