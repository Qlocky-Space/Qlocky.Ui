#ifndef PLATFORM_GLOBAL_INTERNAL_MEDIATOR_H
#define PLATFORM_GLOBAL_INTERNAL_MEDIATOR_H

#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "EventIfc.h"

/**
 * This interface should be extended by all mediator types used in the mediator system.
 * It provides a uniform structure for interaction and management of different mediator implementations.
 */
class Mediator final {
public:

    /**
     * Type alias for a callback function that takes an event of any type.
     */
    using Callback = std::function<void(std::any const&)>;

    /**
     * Subscribes a callback to a specific event type.
     */
    template<typename Event, typename T>
    void subscribe(T* instance, void (T::*method)(Event const&)) {
        subscribe<Event>([instance, method](std::any const& event) {
            (instance->*method)(std::any_cast<Event const&>(event));
        });
    }

    /**
     * Subscribes a callback to a specific event type.
     * The callback will be invoked with the event data when an event of the specified type is
     * published.
     *
     * @tparam T The type of the event to subscribe to.
     * @param callback The callback function to be invoked when the event occurs.
     */
    template<typename T>
    void subscribe(std::function<void(T const&)> callback) {
        static_assert(std::is_base_of<EventIfc, T>::value, "Event must derive from EventIfc");

        auto wrapper = [cb = std::move(callback)](std::any const& event) {
            cb(std::any_cast<T const&>(event));
        };
        m_callbacks[typeid(T)].emplace_back(std::move(wrapper));
    }

    /**
     * Notifies all subscribers of a specific event type.
     * This method will invoke all callbacks registered for the event type with the provided event data.
     * @param event The event data to be passed to the subscribers.
     * @tparam T The type of the event being notified.
     */
    template<typename T>
    void notify(T const& event) {
        static_assert(std::is_base_of<EventIfc, T>::value, "Event must derive from EventIfc");

        auto it = m_callbacks.find(typeid(T));
        if (it != m_callbacks.end()) {
            for (auto const& callback : it->second) {
                callback(event);
            }
        }
    }

    Mediator() = default;
    ~Mediator() = default;

    // Prevent copying and assignment
    Mediator(Mediator const&) = delete;
    Mediator& operator=(Mediator const&) = delete;

    // Allow move semantics
    Mediator(Mediator&&) = default;
    Mediator& operator=(Mediator&&) = default;

private:

    std::unordered_map<std::type_index, std::vector<Callback>> m_callbacks {};
};

#endif