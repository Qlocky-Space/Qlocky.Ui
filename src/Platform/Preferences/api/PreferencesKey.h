#ifndef PREFERENCES_API_PREFERENCES_KEY_H
#define PREFERENCES_API_PREFERENCES_KEY_H

#include <string_view>

/**
 * Represents a key used for preferences storage.
 * @param name The name of the preference key.
 */
class PreferencesKey final {
public:

    /**
     * Constructs a PreferencesKey from a string literal or string_view.
     * @param name The key name.
     */
    constexpr explicit PreferencesKey(std::string_view name) noexcept :
        m_name {name} {
    }

    /**
     * Returns the name of the preference key.
     * @return The key name as a string_view.
     */
    constexpr std::string_view name() const noexcept {
        return m_name;
    }

private:

    std::string_view m_name;
};

#endif