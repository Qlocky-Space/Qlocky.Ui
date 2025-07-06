#ifndef NAVIGATION_URI_H
#define NAVIGATION_URI_H

#include <QString>
#include <string>

/**
 * Represents a Uniform Resource Identifier (URI).
 *
 * The URI consists of a scheme and a path and follows a structure like:
 *      qlocky://settingPage
 *
 * This class provides parsing, validation, and comparison of URIs.
 */
class Uri {
public:

    /**
     * Type alias for the URI scheme (e.g., "qlocky").
     */
    using Scheme = std::string;

    /**
     * Default constructor. Creates an empty, invalid URI.
     */
    Uri() = default;

    explicit Uri(std::string const& str);
    explicit Uri(QString& str);

    /**
     * Checks whether the URI is valid.
     * @return True if the scheme and path are both non-empty.
     */
    bool isValid() const;

    /**
     * @return The scheme portion of the URI.
     */
    Scheme scheme() const;
    void setScheme(Scheme const& scheme);

    /**
     * @return The path portion (everything after the scheme).
     */
    std::string path() const;

    /**
     * Returns the full URI as a string.
     * @return The complete URI (e.g., "qlocky://settingsPage").
     */
    std::string toString() const;

    inline bool operator==(Uri const& uri) const {
        return m_path == uri.m_path && m_scheme == uri.m_scheme;
    }

    inline bool operator!=(Uri const& uri) const {
        return !(*this == uri);
    }

private:

    Scheme m_scheme;
    std::string m_path;
};

#endif