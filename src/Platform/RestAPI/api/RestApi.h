#ifndef SRC_PLATFORM_RESTAPI_API_REST_API_H
#define SRC_PLATFORM_RESTAPI_API_REST_API_H

#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <type_traits>
#include <types/Result.h>

#include "RestApiCode.h"
#include "RestApiRequestOptions.h"
#include "TaskExecutorIfc.h"

/**
 * Generic asynchronous REST API client.
 *
 * The typed convenience methods hide transport details and convert the response
 * body automatically into the requested type via nlohmann::json.
 */
class RestApi {
public:

    using RawResult = Result<std::string, RestApiCode>;
    using RawCallback = std::function<void(RawResult const&)>;

    virtual ~RestApi() = default;

    /**
     * Execute an asynchronous HTTP HEAD request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void head(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Head, options, std::move(callback));
    }

    /**
     * Execute an asynchronous HTTP GET request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void get(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Get, options, std::move(callback));
    }

    /**
     * Execute an asynchronous HTTP POST request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void post(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Post, options, std::move(callback));
    }

    /**
     * Execute an asynchronous HTTP PUT request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void put(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Put, options, std::move(callback));
    }

    /**
     * Execute an asynchronous HTTP PATCH request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void patch(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Patch, options, std::move(callback));
    }

    /**
     * Execute an asynchronous HTTP DELETE request and parse the response into T.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @param callback Callback receiving the typed result.
     */
    template<typename T>
    void remove(RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        request<T>(Method::Delete, options, std::move(callback));
    }

protected:

    explicit RestApi(TaskExecutorIfc& taskExecutor) :
        m_taskExecutor {taskExecutor} {
    }

    enum class Method {
        Head,
        Get,
        Post,
        Put,
        Patch,
        Delete,
    };

    virtual void requestRaw(Method method, RestApiRequestOptions const& options, RawCallback callback) = 0;

private:

    template<typename T>
    void request(Method method, RestApiRequestOptions const& options, std::function<void(Result<T, RestApiCode> const&)> callback) {
        requestRaw(method, options, [this, callback = std::move(callback)](RawResult const& rawResult) mutable {
            if (!callback) {
                return;
            }

            if (rawResult.isError()) {
                RestApiCode const errorCode {rawResult.error()};
                m_taskExecutor.enqueue([callback = std::move(callback), errorCode]() mutable {
                    callback(Result<T, RestApiCode>::error(errorCode));
                });
                return;
            }

            std::string responseBody {rawResult.value()};

            m_taskExecutor.enqueue([callback = std::move(callback), responseBody = std::move(responseBody)]() mutable {
                callback(parseResponse<T>(responseBody));
            });
        });
    }

    template<typename T>
    static Result<T, RestApiCode> parseResponse(std::string const& responseBody) {
        try {
            if constexpr (std::is_same_v<T, std::string>) {
                return Result<T, RestApiCode>::success(responseBody);
            }
            else if constexpr (std::is_same_v<T, nlohmann::json>) {
                return Result<T, RestApiCode>::success(nlohmann::json::parse(responseBody));
            }
            else {
                nlohmann::json const parsedJson {nlohmann::json::parse(responseBody)};
                return Result<T, RestApiCode>::success(parsedJson.get<T>());
            }
        }
        catch (...) {
            return Result<T, RestApiCode>::error(RestApiCode::ParseError);
        }
    }

    TaskExecutorIfc& m_taskExecutor;
};

#endif // SRC_PLATFORM_RESTAPI_API_REST_API_H