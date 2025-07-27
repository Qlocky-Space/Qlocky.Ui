#ifndef OBSERVER_BASE_H
#define OBSERVER_BASE_H

#include <algorithm>
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
            m_observers.push_back(observer);
        }
    }

    /**
     * Remove an observer from the list.
     * @param observer Observer to remove.
     */
    void detach(T* observer) override {
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
    template<class R, typename... Args>
    void notify(R (T::*method)(Args...), Args&&... args) {
        for (auto& observer : m_observers) {
            if (observer) {
                (observer->*method)(std::forward<Args>(args)...);
            }
        }
    }

private:

    std::vector<T*> m_observers;
};

#endif