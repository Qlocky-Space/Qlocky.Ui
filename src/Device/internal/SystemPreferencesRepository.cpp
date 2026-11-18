#include "SystemPreferencesRepository.h"

#include <algorithm>
#include <ng-log/logging.h>

std::string const SystemPreferencesRepository::SYSTEM_PREFERENCES_NAMESPACE {"SystemPreferences"};
std::string const SystemPreferencesRepository::DEFAULT_TIME_ZONE {"Europe/Zurich"};

SystemPreferencesRepository::SystemPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void SystemPreferencesRepository::initialize() {
    // Nothing to do
}

bool SystemPreferencesRepository::isTimeFormat24Hour() {
    auto result {getContext().getBool(Preferences::PROP_24H_FORMAT_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get Time Format: " << result.error();
    }
    return result.valueOr(true);
}

std::string SystemPreferencesRepository::getTimeFormat() {
    return isTimeFormat24Hour() ? "HH:mm" : "hh:mm AP";
}

void SystemPreferencesRepository::setTimeFormat(bool is24HourFormat) {
    auto result {getContext().setBool(Preferences::PROP_24H_FORMAT_KEY, is24HourFormat)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to set time format: " << result.error();
    }
    else {
        // TODO (ALJ): Publish TimeFormatChanged Event
    }
}

std::string SystemPreferencesRepository::getTimeZone() {
    auto result {getContext().getString(Preferences::PROP_TIMEZONE_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get time zone: " << result.error();
    }
    return result.valueOr(DEFAULT_TIME_ZONE);
}

void SystemPreferencesRepository::setTimeZone(std::string const& timeZone) {
    auto result {getContext().setString(Preferences::PROP_TIMEZONE_KEY, timeZone)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to set time zone: " << result.error();
    }
    else {
        // TODO (ALJ): Publish TimeZoneChanged Event
    }
}

uint8_t SystemPreferencesRepository::getDisplayBrightnessPercent() {
    auto result {getContext().getInt(Preferences::PROP_DISPLAY_BRIGHTNESS_PERCENT_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get display brightness: " << result.error();
    }

    int32_t const loaded = result.valueOr(100);
    return static_cast<uint8_t>(std::clamp(loaded, 0, 100));
}

void SystemPreferencesRepository::setDisplayBrightnessPercent(uint8_t brightnessPercent) {
    int32_t const clamped = std::clamp(static_cast<int32_t>(brightnessPercent), 0, 100);
    auto result {getContext().setInt(Preferences::PROP_DISPLAY_BRIGHTNESS_PERCENT_KEY, clamped)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to set display brightness: " << result.error();
    }
}

uint8_t SystemPreferencesRepository::getOutputVolumePercent() {
    auto result {getContext().getInt(Preferences::PROP_OUTPUT_VOLUME_PERCENT_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get output volume: " << result.error();
    }

    int32_t const loaded = result.valueOr(50);
    return static_cast<uint8_t>(std::clamp(loaded, 0, 100));
}

void SystemPreferencesRepository::setOutputVolumePercent(uint8_t volumePercent) {
    int32_t const clamped = std::clamp(static_cast<int32_t>(volumePercent), 0, 100);
    auto result {getContext().setInt(Preferences::PROP_OUTPUT_VOLUME_PERCENT_KEY, clamped)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to set output volume: " << result.error();
    }
}
