#ifndef SRC_PLATFORM_RESTAPI_API_REST_API_CODE_H
#define SRC_PLATFORM_RESTAPI_API_REST_API_CODE_H

/**
 * Generic error codes returned by the REST API module.
 */
enum class RestApiCode {
    NetworkError,
    HttpError,
    ParseError,
    InvalidUrl,
    Canceled,
    Unknown,
};

#endif // SRC_PLATFORM_RESTAPI_API_REST_API_CODE_H