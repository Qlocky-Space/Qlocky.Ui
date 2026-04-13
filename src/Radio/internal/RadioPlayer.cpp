#include "RadioPlayer.h"

#include <ng-log/logging.h>

#include "events/AudioOutputVolumeEvent.h"
#include "events/RadioPlaybackStateChangedEvent.h"

RadioPlayer::RadioPlayer(AudioOutputIfc& audioPlayer, AudioMixerIfc& audioMixer, Mediator& mediator) :
    m_audioPlayer {audioPlayer},
    m_audioMixer {audioMixer},
    m_mediator {mediator} {
    m_audioPlayer.attach(this);
    m_audioMixer.attach(this);
}

RadioPlayer::~RadioPlayer() {
    m_audioMixer.detach(this);
    m_audioPlayer.detach(this);
}

void RadioPlayer::initialize() {
    // TODO this must be loaded from settings, set to 50% for now to avoid blasting users with full volume when they start playback for the first time
    m_audioMixer.setOutputVolume(50);

    m_mediator.notify(AudioOutputVolumeEvent {m_audioMixer.outputVolume()});
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

void RadioPlayer::setPlaying(bool playing) {
    if (m_playing == playing) {
        return;
    }

    m_playing = playing;
    m_mediator.notify(RadioPlaybackStateChangedEvent {m_playing});
}
