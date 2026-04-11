#ifndef SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H
#define SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H

#include <QNetworkAccessManager>

#include "RestApi.h"

/**
 * Qt-backed JSON REST API implementation.
 */
class JsonRestFulApi final : public RestApi {
public:

    JsonRestFulApi();
    ~JsonRestFulApi() final = default;

private:

    void requestRaw(Method method, RestApiRequestOptions const& options, RawCallback callback) final;

    QNetworkAccessManager m_networkAccessManager;
};

#endif // SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H