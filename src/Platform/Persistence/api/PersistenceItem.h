#ifndef PERSISTENCE_API_PERSISTENCE_ITEM_H
#define PERSISTENCE_API_PERSISTENCE_ITEM_H

#include <string_view>

#include "PersistenceKey.h"

/**
 * Represents a raw string type for preferences.
 * This is used because cpp17 does not support constexpr strings.
 */
using RawString = char const*;

template<typename T = std::string>
class PersistenceItem {
public:

    /**
     * Constructs a PersistenceItem with a key and value.
     * @param key The key for the preference item.
     * @param value The value for the preference item.
     */
    constexpr PersistenceItem(PersistenceKey key, T value) :
        m_key {key},
        m_defaultValue {value} {
    }

    /**
     * Constructs a PersistenceItem with a key and value.
     * @param name The name of the preference item, used to create a PersistenceKey.
     * @param value The value for the preference item.
     */
    constexpr PersistenceItem(std::string_view name, T value) :
        PersistenceItem {PersistenceKey {name}, value} {
    }

    /**
     * Returns the key of the preference item.
     * @return The key as a PersistenceKey.
     */
    constexpr PersistenceKey key() const noexcept {
        return m_key;
    }

    /**
     * Returns the default value of the preference item.
     * @return The default value as type T.
     */
    constexpr T defaultValue() const noexcept {
        return m_defaultValue;
    }

    /**
     * Returns the default value as a string view.
     * This is useful for serialization or display purposes.
     * @return The default value as a string view.
     */
    constexpr std::string_view defaultString() const noexcept {
        if constexpr (std::is_same_v<T, std::string>) {
            return m_defaultValue;
        }
        if constexpr (std::is_same_v<T, RawString>) {
            return m_defaultValue;
        }
        else if constexpr (std::is_same_v<T, bool>) {
            return m_defaultValue ? "true" : "false";
        }
        else if constexpr (std::is_integral_v<T>) {
            return std::to_string(m_defaultValue);
        }
        else {
            static_assert("Unsupported type for PersistenceItem");
        }
    }

private:

    PersistenceKey m_key;
    T m_defaultValue;
};

#endif