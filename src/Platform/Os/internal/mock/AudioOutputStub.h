#ifndef SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H
#define SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H

#include <memory>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <string>
#include <Subject.h>

#include "AudioOutputIfc.h"

/// Qt-based audio output stub for WSL2/Docker development environments.
/// Uses QMediaPlayer from Qt6 Multimedia for actual audio playback.
class AudioOutputStub final : public Subject<AudioOutputListenerIfc>, public AudioOutputIfc {
public:

    AudioOutputStub();
    ~AudioOutputStub() final;

    void attach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::attach(observer);
    }

    void detach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::detach(observer);
    }

    AudioOutputResult play(std::string const& source) final;
    AudioOutputResult stop() final;
    bool isPlaying() const final;

private:

    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
    void onError(QMediaPlayer::Error error, QString const& errorString);

    std::unique_ptr<QMediaPlayer> m_player {};
    std::unique_ptr<QAudioOutput> m_audioOutput {};
    std::string m_currentSource {};
};

#endif // SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H
