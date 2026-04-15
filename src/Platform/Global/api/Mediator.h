#ifndef PLATFORM_GLOBAL_INTERNAL_MEDIATOR_H
#define PLATFORM_GLOBAL_INTERNAL_MEDIATOR_H

#include <any>
#include <functional>
#include <memory>
#include <mutex>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "EventIfc.h"
#include "Task.h"
#include "TaskExecutorIfc.h"

/**
 * In-process event mediator used for decoupled communication between modules.
 *
 * Subscribers register interest in a concrete event type derived from EventIfc.
 * Publishers call notify(...) with an event instance, and the mediator forwards
 * that event to all subscribers registered for the exact same event type.
 *
 * Delivery is synchronous by default. A subscriber may opt into asynchronous
 * delivery.
 *
 * The mediator itself is intentionally framework-agnostic. Thread affinity
 * for synchronous delivery can be configured globally, while asynchronous
 * delivery is routed through the shared task executor.
 *
 * Thread-safety:
 * subscribe(...) and notify(...) may be called concurrently while the mediator
 * instance is alive. Subscription storage is protected internally and notify(...)
 * copies the current subscriber list before dispatching callbacks.
 *
 * Lifetime:
 * destruction of the mediator must not race with subscribe(...) or notify(...).
 * The owner is responsible for ensuring all publishers and subscribers stop
 * using the mediator before the mediator instance begins destruction.
 */
class Mediator final {
public:

    /**
     * Controls how a subscriber callback is executed when an event is published.
     */
    enum class DeliveryMode {
        /** Execute the callback immediately in the thread calling notify(...). */
        Sync,

        /** Execute the callback asynchronously on the shared task executor. */
        Async,
    };

    /** Unit of work used by mediator dispatch operations. */
    using WorkItem = std::function<void()>;

    using Dispatcher = std::function<void(WorkItem)>;

    /**
     * Shared event storage passed to internal callback wrappers.
     */
    using EventPayload = std::shared_ptr<std::any const>;

    /**
     * Internal callback type used by the mediator.
     */
    using Callback = std::function<void(EventPayload const&)>;

    /**
     * Per-subscription delivery configuration.
     *
        * Use synchronous() for direct delivery and asynchronous() for background
        * execution.
     */
    struct SubscriptionOptions {
        DeliveryMode deliveryMode {DeliveryMode::Sync};

        /**
         * Create the default synchronous delivery configuration.
         */
        static SubscriptionOptions synchronous() {
            return SubscriptionOptions {};
        }

        /**
         * Create an asynchronous delivery configuration.
         *
         * The callback is executed by the shared task executor service.
         */
        static SubscriptionOptions asynchronous() {
            SubscriptionOptions options {};
            options.deliveryMode = DeliveryMode::Async;
            return options;
        }
    };

    /**
     * Subscribes a callback to a specific event type.
     *
     * This overload is convenient for member-function subscribers that accept
     * direct synchronous delivery.
     *
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @param instance The subscriber instance.
     * @param method The member function invoked for matching events.
     */
    template<typename Event, typename T>
    void subscribe(T* instance, void (T::*method)(Event const&)) {
        subscribe<Event>(instance, method, SubscriptionOptions::synchronous());
    }

    /**
     * Subscribe a coroutine member-function handler to a specific event type.
     *
     * The coroutine is started immediately when the event is dispatched.
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @param instance The subscriber instance.
     * @param method Coroutine member function invoked for matching events.
     */
    template<typename Event, typename T>
    void subscribe(T* instance, DetachedTask (T::*method)(Event const&)) {
        subscribe<Event>(instance, method, SubscriptionOptions::synchronous());
    }

    /**
     * Subscribe a Task-returning member-function handler to a specific event type.
     *
     * The task is detached automatically when the event is dispatched.
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @tparam TResult Task result type.
     * @param instance The subscriber instance.
     * @param method Task-returning member function invoked for matching events.
     */
    template<typename Event, typename T, typename TResult>
    void subscribe(T* instance, ::Task<TResult> (T::*method)(Event const&)) {
        subscribe<Event>(instance, method, SubscriptionOptions::synchronous());
    }

    /**
     * Subscribes a callback to a specific event type with custom delivery options.
     *
    * Use this overload when the subscriber must control whether callbacks are
    * delivered synchronously or asynchronously.
     *
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @param instance The subscriber instance.
     * @param method The member function invoked for matching events.
     * @param options Delivery configuration for this subscription.
     */
    template<typename Event, typename T>
    void subscribe(T* instance, void (T::*method)(Event const&), SubscriptionOptions options) {
        subscribe<Event>([instance, method](Event const& event) {
            (instance->*method)(event);
        },
            std::move(options));
    }

    /**
     * Subscribe a coroutine member-function handler to a specific event type
     * with custom delivery options.
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @param instance The subscriber instance.
     * @param method Coroutine member function invoked for matching events.
     * @param options Delivery configuration for this subscription.
     */
    template<typename Event, typename T>
    void subscribe(T* instance, DetachedTask (T::*method)(Event const&), SubscriptionOptions options) {
        subscribe<Event>([instance, method](Event const& event) {
            (instance->*method)(event);
        },
            std::move(options));
    }

    /**
     * Subscribe a Task-returning member-function handler to a specific event type
     * with custom delivery options.
     * @tparam Event The concrete event type to subscribe to.
     * @tparam T The subscriber type.
     * @tparam TResult Task result type.
     * @param instance The subscriber instance.
     * @param method Task-returning member function invoked for matching events.
     * @param options Delivery configuration for this subscription.
     */
    template<typename Event, typename T, typename TResult>
    void subscribe(T* instance, ::Task<TResult> (T::*method)(Event const&), SubscriptionOptions options) {
        subscribe<Event>([instance, method](Event const& event) {
            detach((instance->*method)(event));
        },
            std::move(options));
    }

    /**
     * Subscribes a callback to a specific event type.
     * The callback will be invoked with the event data when an event of the specified type is
     * published.
     *
     * This overload is convenient for free functions and lambdas using direct
     * synchronous delivery.
     *
     * @tparam T The type of the event to subscribe to.
     * @param callback The callback function to be invoked when the event occurs.
     */
    template<typename T>
    void subscribe(std::function<void(T const&)> callback) {
        subscribe<T>(std::move(callback), SubscriptionOptions::synchronous());
    }

    /**
     * Subscribe a coroutine callback to a specific event type.
     *
     * The coroutine is started immediately when the event is dispatched.
     * @tparam T The type of the event to subscribe to.
     * @param callback Coroutine callback invoked when the event occurs.
     */
    template<typename T>
    void subscribe(std::function<DetachedTask(T const&)> callback) {
        subscribe<T>(std::move(callback), SubscriptionOptions::synchronous());
    }

    /**
     * Subscribe a Task-returning callback to a specific event type.
     *
     * The task is detached automatically when the event is dispatched.
     * @tparam T The type of the event to subscribe to.
     * @tparam TResult Task result type.
     * @param callback Task-returning callback invoked when the event occurs.
     */
    template<typename T, typename TResult>
    void subscribe(std::function<::Task<TResult>(T const&)> callback) {
        subscribe<T, TResult>(std::move(callback), SubscriptionOptions::synchronous());
    }

    /**
    * Subscribes a callback to a specific event type with delivery options.
     *
     * @tparam T The type of the event to subscribe to.
     * @param callback The callback function to be invoked when the event occurs.
    * @param options Delivery mode for this subscription.
     */
    template<typename T>
    void subscribe(std::function<void(T const&)> callback, SubscriptionOptions options) {
        static_assert(std::is_base_of<EventIfc, T>::value, "Event must derive from EventIfc");

        auto wrapper = [cb = std::move(callback)](EventPayload const& event) {
            cb(std::any_cast<T const&>(*event));
        };

        // Protect the subscription registry so subscribe(...) can safely run
        // concurrently with notify(...) or other subscribe(...) calls.
        std::lock_guard<std::mutex> const lock {m_callbacksMutex};
        m_callbacks[typeid(T)].push_back(Subscription {std::move(wrapper), std::move(options)});
    }

    /**
     * Subscribe a coroutine callback to a specific event type with delivery options.
     * @tparam T The type of the event to subscribe to.
     * @param callback Coroutine callback invoked when the event occurs.
     * @param options Delivery mode for this subscription.
     */
    template<typename T>
    void subscribe(std::function<DetachedTask(T const&)> callback, SubscriptionOptions options) {
        static_assert(std::is_base_of<EventIfc, T>::value, "Event must derive from EventIfc");

        auto wrapper = [cb = std::move(callback)](EventPayload const& event) {
            cb(std::any_cast<T const&>(*event));
        };

        std::lock_guard<std::mutex> const lock {m_callbacksMutex};
        m_callbacks[typeid(T)].push_back(Subscription {std::move(wrapper), std::move(options)});
    }

    /**
     * Subscribe a Task-returning callback to a specific event type with delivery options.
     * @tparam T The type of the event to subscribe to.
     * @tparam TResult Task result type.
     * @param callback Task-returning callback invoked when the event occurs.
     * @param options Delivery mode for this subscription.
     */
    template<typename T, typename TResult>
    void subscribe(std::function<::Task<TResult>(T const&)> callback, SubscriptionOptions options) {
        static_assert(std::is_base_of<EventIfc, T>::value, "Event must derive from EventIfc");

        auto wrapper = [cb = std::move(callback)](EventPayload const& event) {
            detach(cb(std::any_cast<T const&>(*event)));
        };

        std::lock_guard<std::mutex> const lock {m_callbacksMutex};
        m_callbacks[typeid(T)].push_back(Subscription {std::move(wrapper), std::move(options)});
    }

    /**
     * Notifies all subscribers of a specific event type.
     * This method will invoke all callbacks registered for the event type with the provided event data.
     *
     * The mediator matches subscribers by exact event type. It does not perform
     * inheritance-based routing.
     *
    * notify(...) returns after all synchronous subscribers have run and after
    * asynchronous subscribers have been scheduled. It does
     * not wait for asynchronous work to finish.
     *
     * @param event The event data to be passed to the subscribers.
     * @tparam T The type of the event being notified.
     */
    template<typename T>
    void notify(T event) {
        using EventType = std::decay_t<T>;

        static_assert(std::is_base_of<EventIfc, EventType>::value, "Event must derive from EventIfc");

        std::vector<Subscription> subscriptions {};
        {
            // Copy the matching subscribers while holding the registry lock,
            // then release the lock before executing any user callback. This
            // avoids calling back into user code while internal mediator state
            // is locked and prevents callback-induced deadlocks.
            std::lock_guard<std::mutex> const lock {m_callbacksMutex};
            auto const it = m_callbacks.find(typeid(EventType));
            if (it == m_callbacks.end()) {
                return;
            }

            subscriptions = it->second;
        }

        EventPayload const payload {std::make_shared<std::any>(std::move(event))};
        for (Subscription const& subscription : subscriptions) {
            dispatch(subscription, payload);
        }
    }

    /**
     * Constructs a Mediator with the given task executor for asynchronous deliveries.
     * @param taskExecutor The shared task executor used for asynchronous callback execution.
     */
    explicit Mediator(TaskExecutorIfc& taskExecutor) :
        m_taskExecutor {taskExecutor},
        m_synchronousDispatcher {},
        m_callbacks {},
        m_callbacksMutex {},
        m_dispatcherMutex {} {
    }

    /**
     * Sets the default dispatcher for synchronous subscriptions.
     *
     * When configured, subscriptions with SubscriptionOptions::synchronous()
     * run through this dispatcher. This is typically used to bind synchronous
     * callbacks to the UI thread.
     *
     * @param dispatcher Dispatcher used for synchronous subscriptions.
     */
    void setSynchronousDispatcher(Dispatcher dispatcher) {
        std::lock_guard<std::mutex> const lock {m_dispatcherMutex};
        m_synchronousDispatcher = std::move(dispatcher);
    }

    ~Mediator() = default;

    // Prevent copying and assignment
    Mediator(Mediator const&) = delete;
    Mediator& operator=(Mediator const&) = delete;

    // Moving would invalidate worker coordination state and subscription storage.
    Mediator(Mediator&&) = delete;
    Mediator& operator=(Mediator&&) = delete;

private:

    struct Subscription {
        Callback callback {};
        SubscriptionOptions options {};
    };

    /**
     * Execute a task according to the subscription delivery configuration.
     *
     * Synchronous delivery runs via the configured synchronous dispatcher when
     * available, otherwise in the calling thread. Asynchronous delivery is
     * submitted to the shared executor.
     */
    void executeTask(SubscriptionOptions const& options, WorkItem task) {
        if (options.deliveryMode == DeliveryMode::Async) {
            m_taskExecutor.enqueue(std::move(task));
            return;
        }

        Dispatcher synchronousDispatcher {};
        {
            std::lock_guard<std::mutex> const lock {m_dispatcherMutex};
            synchronousDispatcher = m_synchronousDispatcher;
        }

        if (synchronousDispatcher) {
            synchronousDispatcher(std::move(task));
            return;
        }

        task();
    }

    /**
     * Schedule or execute one subscriber callback for the given payload.
     *
     * The event payload is reference-counted so asynchronous deliveries can keep
     * the event alive until the callback has actually run.
     */
    void dispatch(Subscription const& subscription, EventPayload const& payload) {
        executeTask(subscription.options, [callback = subscription.callback, payload]() {
            callback(payload);
        });
    }

    TaskExecutorIfc& m_taskExecutor;
    Dispatcher m_synchronousDispatcher;
    std::unordered_map<std::type_index, std::vector<Subscription>> m_callbacks;
    std::mutex m_callbacksMutex;
    std::mutex m_dispatcherMutex;
};

#endif