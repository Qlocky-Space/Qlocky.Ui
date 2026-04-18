#include "SystemPreferencesRepository.h"

#include <algorithm>
#include <ng-log/logging.h>

std::string const SystemPreferencesRepository::SYSTEM_PREFERENCES_NAMESPACE {"SystemPreferences"};

SystemPreferencesRepository::SystemPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void SystemPreferencesRepository::initialize() {
    // Nothing to do
}

std::string SystemPreferencesRepository::getTimeFormat() {
    auto result {getContext().getBool(Preferences::PROP_24H_FORMAT_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get time format: " << result.error();
    }

    bool is24HourFormat {result.valueOr(true)};
    return is24HourFormat ? "HH:mm" : "hh:mm AP";
}

std::string SystemPreferencesRepository::getTimeZone() {
    auto result {getContext().getString(Preferences::PROP_TIMEZONE_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get time zone: " << result.error();
    }
    // Default to UTC+02:00 if not set
    std::string const prefTimeZone {result.valueOr("UTC+02:00")};

    return prefTimeZone;
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
