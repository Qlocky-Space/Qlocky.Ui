#include "RadioPlayer.h"

#include <algorithm>
#include <ng-log/logging.h>

#include "events/ApplicationStartedEvent.h"
#include "events/AudioOutputVolumeEvent.h"
#include "events/RadioPlaybackStateChangedEvent.h"

RadioPlayer::RadioPlayer(AudioOutputIfc& audioPlayer, AudioMixerIfc& audioMixer, Mediator& mediator, SystemPreferencesRepositoryIfc& systemPreferences) :
    m_audioPlayer {audioPlayer},
    m_audioMixer {audioMixer},
    m_mediator {mediator},
    m_systemPreferences {systemPreferences} {
    m_audioPlayer.attach(this);
    m_audioMixer.attach(this);
    m_mediator.subscribe<ApplicationStartedEvent>(this, &RadioPlayer::onApplicationStarted);
}

RadioPlayer::~RadioPlayer() {
    m_audioMixer.detach(this);
    m_audioPlayer.detach(this);
}

void RadioPlayer::initialize() {
    // Nothing to do
}

void RadioPlayer::play(RadioEntity const& radio) {
    if (radio.url.empty()) {
        LOG(WARNING) << "Selected radio has no playback URL";
        setPlaying(false);
        return;
    }

    auto const playResult = m_audioPlayer.play(radio.url);
    if (playResult.isError()) {
        LOG(WARNING) << "Failed to start audio playback for stream url: " << radio.url;
        setPlaying(false);
        return;
    }
}

void RadioPlayer::stop() {
    auto const stopResult = m_audioPlayer.stop();
    if (stopResult.isError()) {
        LOG(WARNING) << "Failed to stop audio playback";
        setPlaying(false);
    }
}

bool RadioPlayer::isPlaying() const {
    return m_playing;
}

void RadioPlayer::setOutputVolume(uint8_t volumePercent) {
    persistVolume(volumePercent);
    m_audioMixer.setOutputVolume(volumePercent);
}

void RadioPlayer::onPlaybackStarted(std::string const& source) {
    setPlaying(true);
}

void RadioPlayer::onPlaybackStopped() {
    setPlaying(false);
}

void RadioPlayer::onPlaybackFailed(AudioOutputErrorCode errorCode) {
    setPlaying(false);
}

void RadioPlayer::onVolumeChanged(uint8_t volumePercent) {
    m_mediator.notify(AudioOutputVolumeEvent {volumePercent});
}

void RadioPlayer::onApplicationStarted(ApplicationStartedEvent const&) {
    uint8_t const clamped = static_cast<uint8_t>(std::clamp(static_cast<int32_t>(m_systemPreferences.getOutputVolumePercent()), 0, 100));
    m_audioMixer.setOutputVolume(clamped);

    m_mediator.notify(AudioOutputVolumeEvent {clamped});
}

void RadioPlayer::persistVolume(uint8_t volumePercent) {
    m_systemPreferences.setOutputVolumePercent(volumePercent);
}

void RadioPlayer::setPlaying(bool playing) {
    if (m_playing == playing) {
        return;
    }

    m_playing = playing;
    m_mediator.notify(RadioPlaybackStateChangedEvent {m_playing});
}
