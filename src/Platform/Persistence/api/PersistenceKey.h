#ifndef PERSISTENCE_API_PERSISTENCE_KEY_H
#define PERSISTENCE_API_PERSISTENCE_KEY_H

#include <string_view>

/**
 * Represents a key used for preferences storage.
 * @param name The name of the preference key.
 */
class PersistenceKey final {
public:

    /**
     * Constructs a PersistenceKey from a string literal or string_view.
     * @param name The key name.
     */
    constexpr explicit PersistenceKey(std::string_view name) noexcept :
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