#include "DisplayService.h"

#include <algorithm>

#include "events/ApplicationStartedEvent.h"
#include "events/DisplayBrightnessChangedEvent.h"

namespace {

uint8_t clampBrightness(uint8_t brightnessPercent) {
    return static_cast<uint8_t>(std::clamp(static_cast<int32_t>(brightnessPercent), 0, 100));
}

uint8_t toDimLevel(uint8_t brightnessPercent) {
    return static_cast<uint8_t>(100U - brightnessPercent);
}

} // namespace

DisplayService::DisplayService(Mediator& mediator, DisplayControlIfc& displayControl, SystemPreferencesRepositoryIfc& systemPreferences) :
    m_mediator {mediator},
    m_displayControl {displayControl},
    m_systemPreferences {systemPreferences} {
    m_mediator.subscribe<ApplicationStartedEvent>(this, &DisplayService::onApplicationStarted);
}

DisplayService::~DisplayService() {
    // Ensure display is turned on when service is destroyed to avoid leaving it in a dimmed state.
    m_displayControl.turnOn();
    m_displayControl.dim(20);
}

void DisplayService::initialize() {
    m_displayControl.turnOn();
    m_displayControl.dim(20);
}

void DisplayService::setBrightnessPercent(uint8_t brightnessPercent) {
    uint8_t const clamped = clampBrightness(brightnessPercent);
    m_systemPreferences.setDisplayBrightnessPercent(clamped);
    m_displayControl.dim(toDimLevel(clamped));
    m_mediator.notify(DisplayBrightnessChangedEvent {clamped});
}

void DisplayService::onApplicationStarted(ApplicationStartedEvent const&) {
    uint8_t const brightnessPercent = clampBrightness(m_systemPreferences.getDisplayBrightnessPercent());
    m_displayControl.dim(toDimLevel(brightnessPercent));
    m_mediator.notify(DisplayBrightnessChangedEvent {brightnessPercent});
}