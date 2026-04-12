#ifndef SRC_PLATFORM_OS_API_AUDIO_OUTPUT_IFC_H
#define SRC_PLATFORM_OS_API_AUDIO_OUTPUT_IFC_H

#include <string>

#include "AudioOutputErrorCode.h"
#include "AudioOutputListenerIfc.h"
#include "SubjectIfc.h"

/**
 * OS abstraction for audio playback.
 * This interface hides platform specific playback backends from higher modules.
 */
class AudioOutputIfc : public SubjectIfc<AudioOutputListenerIfc> {
public:

    virtual ~AudioOutputIfc() = default;

    /**
     * Start playback for the given source.
     * @param source The source URL or identifier to play.
     * @return Result indicating success or failure.
     */
    virtual AudioOutputResult play(std::string const& source) = 0;

    /**
     * Stop playback.
     * @return Result indicating success or failure.
     */
    virtual AudioOutputResult stop() = 0;

    /**
     * @return True if playback is active.
     */
    virtual bool isPlaying() const = 0;
};

#endif // SRC_PLATFORM_OS_API_AUDIO_OUTPUT_IFC_H
