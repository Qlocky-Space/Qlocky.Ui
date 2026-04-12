#ifndef SRC_PLATFORM_OS_API_AUDIO_OUTPUT_LISTENER_IFC_H
#define SRC_PLATFORM_OS_API_AUDIO_OUTPUT_LISTENER_IFC_H

#include <string>

#include "AudioOutputErrorCode.h"

/**
 * Observer interface for OS audio player state changes.
 */
class AudioOutputListenerIfc {
public:

    virtual ~AudioOutputListenerIfc() = default;

    /**
     * Called when playback has started for a source.
     * @param source The played source URL or identifier.
     */
    virtual void onPlaybackStarted(std::string const& source) = 0;

    /**
     * Called when playback has stopped.
     */
    virtual void onPlaybackStopped() = 0;

    /**
     * Called when playback failed.
     * @param errorCode The backend error code.
     */
    virtual void onPlaybackFailed(AudioOutputErrorCode errorCode) = 0;
};

#endif // SRC_PLATFORM_OS_API_AUDIO_OUTPUT_LISTENER_IFC_H
