#ifndef SRC_PLATFORM_RESTAPI_API_REST_API_REQUEST_OPTIONS_H
#define SRC_PLATFORM_RESTAPI_API_REST_API_REQUEST_OPTIONS_H

#include <string>
#include <vector>

/**
 * HTTP header entry used by RestApiRequestOptions.
 */
struct RestApiHeader {
    std::string name;
    std::string value;
};

/**
 * Generic options for one REST API request.
 */
struct RestApiRequestOptions {
    std::string url;
    std::vector<RestApiHeader> headers {};
    std::string body {};
    std::string contentType {"application/json; charset=utf-8"};
};

#endif // SRC_PLATFORM_RESTAPI_API_REST_API_REQUEST_OPTIONS_H