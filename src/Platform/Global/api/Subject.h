#ifndef OBSERVER_BASE_H
#define OBSERVER_BASE_H

#include <algorithm>
#include <mutex>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "SubjectIfc.h"

/**
 * Base class for observer pattern implementation.
 * This class provides methods to attach and detach observers.
 * It is designed to be inherited by classes that need to notify observers of events.
 * @tparam T Type of the observer interface.
 */
template<typename T>
class Subject : public SubjectIfc<T> {
public:

    virtual ~Subject() = default;

    /**
     * Add an observer to the list.
     * @param observer Observer to add.
     */
    void attach(T* observer) override {
        if (observer) {
            std::lock_guard<std::mutex> lock {m_observersMutex};
            m_observers.push_back(observer);
        }
    }

    /**
     * Remove an observer from the list.
     * @param observer Observer to remove.
     */
    void detach(T* observer) override {
        std::lock_guard<std::mutex> lock {m_observersMutex};
        auto it = std::remove(m_observers.begin(), m_observers.end(), observer);
        if (it != m_observers.end()) {
            m_observers.erase(it, m_observers.end());
        }
    }

protected:

    /**
     * Notify the observer of an event.
     * @param eventId Identifier for the event.
     * @param data Optional data associated with the event.
     */
    template<class R, typename A>
    void notify(R (T::*method)(A&), A& arg) {
        std::vector<T*> observers {};
        {
            std::lock_guard<std::mutex> lock {m_observersMutex};
            observers = m_observers;
        }

        for (T* observer : observers) {
            if (observer) {
                (observer->*method)(arg);
            }
        }
    }

    template<class R, typename... Args, typename... CallArgs>
    void notify(R (T::*method)(Args...), CallArgs&&... callArgs) {
        static_assert(sizeof...(Args) == sizeof...(CallArgs), "Observer argument count mismatch");

        using ArgsTuple = std::tuple<std::conditional_t<std::is_reference_v<CallArgs>, CallArgs, std::decay_t<CallArgs>>...>;
        ArgsTuple argsTuple {std::forward<CallArgs>(callArgs)...};

        std::vector<T*> observers {};
        {
            std::lock_guard<std::mutex> lock {m_observersMutex};
            observers = m_observers;
        }

        for (T* observer : observers) {
            if (observer) {
                std::apply([observer, method](auto&... args) {
                    (observer->*method)(args...);
                },
                    argsTuple);
            }
        }
    }

private:

    std::mutex m_observersMutex {};
    std::vector<T*> m_observers;
};

#endif