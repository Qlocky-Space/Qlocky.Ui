#ifndef SRC_PLATFORM_OS_API_AUDIO_OUTPUT_ERROR_CODE_H
#define SRC_PLATFORM_OS_API_AUDIO_OUTPUT_ERROR_CODE_H

#include <types/Result.h>

/**
 * Error codes for OS-level audio playback operations.
 */
enum class AudioOutputErrorCode {
    SUCCESS = 0,
    ERROR_GENERIC = -1,
    ERROR_INVALID_ARGUMENT = -2,
    ERROR_NOT_SUPPORTED = -3,
    ERROR_BACKEND_NOT_AVAILABLE = -4,
    ERROR_START_FAILED = -5,
    ERROR_STOP_FAILED = -6,
};

/**
 * Short hand for Result type specialized for AudioOutputErrorCode.
 */
using AudioOutputResult = Result<bool, AudioOutputErrorCode>;

#endif // SRC_PLATFORM_OS_API_AUDIO_OUTPUT_ERROR_CODE_H
