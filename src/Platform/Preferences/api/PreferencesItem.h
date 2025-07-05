#ifndef PREFERENCES_API_PREFERENCES_ITEM_H
#define PREFERENCES_API_PREFERENCES_ITEM_H

#include <string_view>

#include "PreferencesKey.h"

/**
 * Represents a raw string type for preferences.
 * This is used because cpp17 does not support constexpr strings.
 */
using RawString = char const*;

template<typename T = std::string>
class PreferencesItem {
public:

    /**
     * Constructs a PreferencesItem with a key and value.
     * @param key The key for the preference item.
     * @param value The value for the preference item.
     */
    constexpr PreferencesItem(PreferencesKey key, T value) :
        m_key {key},
        m_defaultValue {value} {
    }

    /**
     * Constructs a PreferencesItem with a key and value.
     * @param name The name of the preference item, used to create a PreferencesKey.
     * @param value The value for the preference item.
     */
    constexpr PreferencesItem(std::string_view name, T value) :
        PreferencesItem {PreferencesKey {name}, value} {
    }

    /**
     * Returns the key of the preference item.
     * @return The key as a PreferencesKey.
     */
    constexpr PreferencesKey key() const noexcept {
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
            static_assert("Unsupported type for PreferencesItem");
        }
    }

private:

    PreferencesKey m_key;
    T m_defaultValue;
};

#endif