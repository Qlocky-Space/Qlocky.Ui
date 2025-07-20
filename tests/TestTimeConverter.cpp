#include <gmock/gmock.h>

#include "internal/AlarmPreferencesRepositoryIfc.h"
#include "view/TimeConverter.h"

using namespace ::testing;

class AlarmPreferencesRepositoryMock : public AlarmPreferencesRepositoryIfc {
public:

    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(std::string, getTimeFormat, (), (override));
    MOCK_METHOD(std::string, getTimeZone, (), (override));
};

TEST(TimeConverter, relativeTimeToUtc) {
    NiceMock<AlarmPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.relativeTimeToUtc(48000);
    ASSERT_EQ(result, 40800);
}

TEST(TimeConverter, utcToRelativeTime) {
    NiceMock<AlarmPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.utcToRelativeTime(40800);
    ASSERT_EQ(result, 48000);
}

TEST(TimeConverter, asTime) {
    NiceMock<AlarmPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.asTime(1753010220);
    ASSERT_EQ(result.toStdString(), std::string("13:17"));
}