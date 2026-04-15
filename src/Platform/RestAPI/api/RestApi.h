#ifndef SRC_PLATFORM_RESTAPI_API_REST_API_H
#define SRC_PLATFORM_RESTAPI_API_REST_API_H

#include <functional>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <Task.h>
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
     * Execute an asynchronous HTTP HEAD request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> head(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Head, options);
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
     * Execute an asynchronous HTTP GET request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> get(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Get, options);
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
     * Execute an asynchronous HTTP POST request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> post(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Post, options);
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
     * Execute an asynchronous HTTP PUT request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> put(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Put, options);
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
     * Execute an asynchronous HTTP PATCH request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> patch(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Patch, options);
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

    /**
     * Execute an asynchronous HTTP DELETE request and co_await the parsed response.
     * @tparam T Parsed response type.
     * @param options Request options.
     * @return Task resolving to the typed result.
     */
    template<typename T>
    Task<Result<T, RestApiCode>> remove(RestApiRequestOptions const& options) {
        co_return co_await requestAsync<T>(Method::Delete, options);
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
    struct RequestState {
        std::mutex mutex {};
        bool isCompleted {false};
        bool isSuspending {false};
        std::optional<Result<T, RestApiCode>> result {};
        std::coroutine_handle<> continuation {};
    };

    template<typename T>
    struct RequestAwaiter {
        RestApi& api;
        Method method;
        RestApiRequestOptions options;
        std::shared_ptr<RequestState<T>> state {std::make_shared<RequestState<T>>()};

        bool await_ready() const noexcept {
            return false;
        }

        bool await_suspend(std::coroutine_handle<> continuation) {
            {
                std::lock_guard<std::mutex> lock {state->mutex};
                state->continuation = continuation;
                state->isSuspending = true;
            }

            api.request<T>(method, options, [state = state](Result<T, RestApiCode> const& result) mutable {
                std::coroutine_handle<> continuationToResume {};

                {
                    std::lock_guard<std::mutex> lock {state->mutex};
                    state->result = result;
                    state->isCompleted = true;
                    if (!state->isSuspending) {
                        continuationToResume = state->continuation;
                    }
                }

                if (continuationToResume) {
                    continuationToResume.resume();
                }
            });

            std::lock_guard<std::mutex> lock {state->mutex};
            state->isSuspending = false;
            return !state->isCompleted;
        }

        Result<T, RestApiCode> await_resume() {
            std::lock_guard<std::mutex> lock {state->mutex};
            return *state->result;
        }
    };

    template<typename T>
    Task<Result<T, RestApiCode>> requestAsync(Method method, RestApiRequestOptions const& options) {
        co_return co_await RequestAwaiter<T> {*this, method, options};
    }

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