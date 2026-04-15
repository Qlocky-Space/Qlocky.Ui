#ifndef SRC_PLATFORM_GLOBAL_API_TASK_H
#define SRC_PLATFORM_GLOBAL_API_TASK_H

#include <coroutine>
#include <exception>
#include <optional>
#include <type_traits>
#include <utility>

template<typename T>
class Task;

namespace task_detail {

template<typename T>
struct TaskPromise;

template<typename T>
struct TaskFinalAwaiter {
    bool await_ready() const noexcept {
        return false;
    }

    std::coroutine_handle<> await_suspend(std::coroutine_handle<TaskPromise<T>> coroutine) const noexcept {
        std::coroutine_handle<> const continuation {coroutine.promise().continuation};
        if (continuation) {
            return continuation;
        }

        return std::noop_coroutine();
    }

    void await_resume() const noexcept {
    }
};

template<typename T>
struct TaskPromiseBase {
    std::coroutine_handle<> continuation {};
    std::exception_ptr exception {};

    std::suspend_always initial_suspend() const noexcept {
        return {};
    }

    TaskFinalAwaiter<T> final_suspend() const noexcept {
        return {};
    }

    void unhandled_exception() {
        exception = std::current_exception();
    }
};

template<typename T>
struct TaskPromise final : TaskPromiseBase<T> {
    std::optional<T> value {};

    Task<T> get_return_object();

    void return_value(T valueToStore) {
        value = std::move(valueToStore);
    }

    T result() {
        if (this->exception) {
            std::rethrow_exception(this->exception);
        }

        return std::move(*value);
    }
};

template<>
struct TaskPromise<void> final : TaskPromiseBase<void> {
    Task<void> get_return_object();

    void return_void() noexcept {
    }

    void result() {
        if (this->exception) {
            std::rethrow_exception(this->exception);
        }
    }
};

} // namespace task_detail

/**
 * Coroutine task representing one asynchronously produced result.
 *
 * A Task<T> is lazy and starts execution when first awaited.
 *
 * @tparam T Result value type.
 */
template<typename T>
class Task final {
public:

    using promise_type = task_detail::TaskPromise<T>;

    Task() = default;

    explicit Task(std::coroutine_handle<promise_type> coroutine) :
        m_coroutine {coroutine} {
    }

    Task(Task const&) = delete;
    Task& operator=(Task const&) = delete;

    Task(Task&& other) noexcept :
        m_coroutine {std::exchange(other.m_coroutine, {})} {
    }

    Task& operator=(Task&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (m_coroutine) {
            m_coroutine.destroy();
        }

        m_coroutine = std::exchange(other.m_coroutine, {});
        return *this;
    }

    ~Task() {
        if (m_coroutine) {
            m_coroutine.destroy();
        }
    }

    auto operator co_await() && noexcept {
        struct Awaiter {
            std::coroutine_handle<promise_type> coroutine;

            ~Awaiter() {
                if (coroutine) {
                    coroutine.destroy();
                }
            }

            bool await_ready() const noexcept {
                return !coroutine || coroutine.done();
            }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<> continuation) noexcept {
                coroutine.promise().continuation = continuation;
                return coroutine;
            }

            T await_resume() {
                return coroutine.promise().result();
            }
        };

        return Awaiter {std::exchange(m_coroutine, {})};
    }

private:

    std::coroutine_handle<promise_type> m_coroutine {};
};

template<>
class Task<void> final {
public:

    using promise_type = task_detail::TaskPromise<void>;

    Task() = default;

    explicit Task(std::coroutine_handle<promise_type> coroutine) :
        m_coroutine {coroutine} {
    }

    Task(Task const&) = delete;
    Task& operator=(Task const&) = delete;

    Task(Task&& other) noexcept :
        m_coroutine {std::exchange(other.m_coroutine, {})} {
    }

    Task& operator=(Task&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (m_coroutine) {
            m_coroutine.destroy();
        }

        m_coroutine = std::exchange(other.m_coroutine, {});
        return *this;
    }

    ~Task() {
        if (m_coroutine) {
            m_coroutine.destroy();
        }
    }

    auto operator co_await() && noexcept {
        struct Awaiter {
            std::coroutine_handle<promise_type> coroutine;

            ~Awaiter() {
                if (coroutine) {
                    coroutine.destroy();
                }
            }

            bool await_ready() const noexcept {
                return !coroutine || coroutine.done();
            }

            std::coroutine_handle<> await_suspend(std::coroutine_handle<> continuation) noexcept {
                coroutine.promise().continuation = continuation;
                return coroutine;
            }

            void await_resume() {
                coroutine.promise().result();
            }
        };

        return Awaiter {std::exchange(m_coroutine, {})};
    }

private:

    std::coroutine_handle<promise_type> m_coroutine {};
};

template<typename T>
Task<T> task_detail::TaskPromise<T>::get_return_object() {
    return Task<T> {std::coroutine_handle<TaskPromise<T>>::from_promise(*this)};
}

inline Task<void> task_detail::TaskPromise<void>::get_return_object() {
    return Task<void> {std::coroutine_handle<TaskPromise<void>>::from_promise(*this)};
}

/**
 * Fire-and-forget coroutine used for top-level async workflows.
 */
class DetachedTask final {
public:

    struct promise_type {
        DetachedTask get_return_object() const noexcept {
            return {};
        }

        std::suspend_never initial_suspend() const noexcept {
            return {};
        }

        struct FinalAwaiter {
            bool await_ready() const noexcept {
                return false;
            }

            void await_suspend(std::coroutine_handle<promise_type> coroutine) const noexcept {
                coroutine.destroy();
            }

            void await_resume() const noexcept {
            }
        };

        FinalAwaiter final_suspend() const noexcept {
            return {};
        }

        void return_void() const noexcept {
        }

        void unhandled_exception() const {
            std::terminate();
        }
    };
};

/**
 * Start a task without awaiting it at the call site.
 *
 * This helper is intended for boundaries that need to launch coroutine-based
 * work from callback-style APIs.
 *
 * @tparam T Task result type.
 * @param task Task to execute.
 * @return Detached task that starts immediately.
 */
template<typename T>
DetachedTask detach(Task<T> task) {
    if constexpr (std::is_void_v<T>) {
        co_await std::move(task);
    }
    else {
        static_cast<void>(co_await std::move(task));
    }
}

#endif // SRC_PLATFORM_GLOBAL_API_TASK_H