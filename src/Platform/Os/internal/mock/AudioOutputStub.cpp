#include "AudioOutputStub.h"

#include <ng-log/logging.h>

AudioOutputStub::AudioOutputStub() :
    m_player {std::make_unique<QMediaPlayer>()},
    m_audioOutput {std::make_unique<QAudioOutput>()} {
    m_player->setAudioOutput(m_audioOutput.get());

    QObject::connect(m_player.get(), &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
        onMediaStatusChanged(status);
    });
    QObject::connect(m_player.get(), &QMediaPlayer::playbackStateChanged, [this](QMediaPlayer::PlaybackState state) {
        onPlaybackStateChanged(state);
    });
    QObject::connect(m_player.get(), QOverload<QMediaPlayer::Error, QString const&>::of(&QMediaPlayer::errorOccurred),
        [this](QMediaPlayer::Error error, QString const& errorString) {
            onError(error, errorString);
        });
}

AudioOutputStub::~AudioOutputStub() {
    if (m_player) {
        m_player->stop();
    }
}

AudioOutputResult AudioOutputStub::play(std::string const& source) {
    if (source.empty()) {
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
    }

    stop();

    m_currentSource = source;
    m_player->setSource(QUrl {QString::fromStdString(source)});
    m_player->play();

    notify(&AudioOutputListenerIfc::onPlaybackStarted, source);
    return AudioOutputResult::success(true);
}

AudioOutputResult AudioOutputStub::stop() {
    if (m_player->playbackState() == QMediaPlayer::StoppedState) {
        return AudioOutputResult::success(true);
    }

    m_player->stop();
    m_currentSource.clear();
    notify(&AudioOutputListenerIfc::onPlaybackStopped);
    return AudioOutputResult::success(true);
}

bool AudioOutputStub::isPlaying() const {
    return m_player->playbackState() == QMediaPlayer::PlayingState;
}

void AudioOutputStub::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    // Handle media status changes if needed (e.g., LoadedMedia, BufferingMedia)
    Q_UNUSED(status);
}

void AudioOutputStub::onPlaybackStateChanged(QMediaPlayer::PlaybackState state) {
    // Handle playback state changes
    Q_UNUSED(state);
}

void AudioOutputStub::onError(QMediaPlayer::Error error, QString const& errorString) {
    if (error == QMediaPlayer::NoError) {
        return;
    }

    LOG(WARNING) << "QMediaPlayer error: " << errorString.toStdString();

    switch (error) {
        case QMediaPlayer::ResourceError:
            notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_START_FAILED);
            break;
        case QMediaPlayer::FormatError:
        case QMediaPlayer::AccessDeniedError:
            notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
            break;
        default:
            notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_BACKEND_NOT_AVAILABLE);
            break;
    }
}
