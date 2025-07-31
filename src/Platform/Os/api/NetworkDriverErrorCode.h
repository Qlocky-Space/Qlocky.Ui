#ifndef NETWORK_DRIVER_ERROR_CODE_H
#define NETWORK_DRIVER_ERROR_CODE_H

#include <types/Result.h>

/**
 * Enum class representing error codes for network driver operations.
 * These error codes are used to indicate the status of various network operations.
 */
enum class NetworkDriverErrorCode {
    SUCCESS = 0,
    ERROR_GENERIC = -1,
    ERROR_NOT_SUPPORTED = -2,
    ERROR_INVALID_ARGUMENT = -3,
    ERROR_TIMEOUT = -4,
    ERROR_PERMISSION_DENIED = -5,
    ERROR_NETWORK_UNREACHABLE = -6,
    ERROR_CONNECTION_FAILED = -7,
    ERROR_SCAN_FAILED = -8,
    ERROR_ABORTED = -9
};

/**
 * Short hand for Result type specialized for NetworkDriverErrorCode.
 */
using NetworkResult = Result<bool, NetworkDriverErrorCode>;

#endif