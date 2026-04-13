#ifndef SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H
#define SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H

#include <QNetworkAccessManager>

#include "RestApi.h"
#include "TaskExecutorIfc.h"

/**
 * JSON REST API client implementation using Qt's QNetworkAccessManager.
 */
class JsonRestFulApi final : public RestApi {
public:

    explicit JsonRestFulApi(TaskExecutorIfc& taskExecutor);
    ~JsonRestFulApi() final = default;

protected:

    /// @see RestApi::requestRaw
    void requestRaw(Method method, RestApiRequestOptions const& options, RawCallback callback) final;

private:

    QNetworkAccessManager m_networkAccessManager {};
};

#endif // SRC_PLATFORM_RESTAPI_INTERNAL_JSON_REST_FUL_API_H