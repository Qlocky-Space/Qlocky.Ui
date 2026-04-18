#include <gmock/gmock.h>

#include "SystemPreferencesRepositoryIfc.h"
#include "view/TimeConverter.h"

using namespace ::testing;

class SystemPreferencesRepositoryMock : public SystemPreferencesRepositoryIfc {
public:

    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(std::string, getTimeFormat, (), (override));
    MOCK_METHOD(std::string, getTimeZone, (), (override));
    MOCK_METHOD(uint8_t, getDisplayBrightnessPercent, (), (override));
    MOCK_METHOD(void, setDisplayBrightnessPercent, (uint8_t brightnessPercent), (override));
    MOCK_METHOD(uint8_t, getOutputVolumePercent, (), (override));
    MOCK_METHOD(void, setOutputVolumePercent, (uint8_t volumePercent), (override));
};

TEST(TimeConverter, relativeTimeToUtc) {
    NiceMock<SystemPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.relativeTimeToUtc(48000);
    ASSERT_EQ(result, 40800);
}

TEST(TimeConverter, utcToRelativeTime) {
    NiceMock<SystemPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.utcToRelativeTime(40800);
    ASSERT_EQ(result, 48000);
}

TEST(TimeConverter, asTime) {
    NiceMock<SystemPreferencesRepositoryMock> preferencesMock {};
    ON_CALL(preferencesMock, getTimeFormat()).WillByDefault(Return("HH:mm"));
    ON_CALL(preferencesMock, getTimeZone()).WillByDefault(Return("UTC+02:00"));

    TimeConverter testObject {preferencesMock};

    auto result = testObject.asTime(1753010220);
    ASSERT_EQ(result.toStdString(), std::string("13:17"));
}