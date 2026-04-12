#include "AudioOutputStub.h"

AudioOutputResult AudioOutputStub::play(std::string const& source) {
    if (source.empty()) {
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
    }

    m_currentSource = source;
    m_playing = true;
    notify(&AudioOutputListenerIfc::onPlaybackStarted, source);
    return AudioOutputResult::success(true);
}

AudioOutputResult AudioOutputStub::stop() {
    if (!m_playing) {
        return AudioOutputResult::success(true);
    }

    m_playing = false;
    m_currentSource.clear();
    notify(&AudioOutputListenerIfc::onPlaybackStopped);
    return AudioOutputResult::success(true);
}
