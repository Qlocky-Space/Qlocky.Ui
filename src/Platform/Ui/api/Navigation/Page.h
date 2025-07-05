#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <string>

/**
 * Represents a page in the navigation system.
 */
struct Page {
    std::string name; ///< The name of the page.
    std::string url;  ///< The URL associated with the page.

    /**
     * Constructs a Page with the given name and URL.
     * @param name The name of the page.
     * @param url The URL of the page.
     */
    Page(std::string const name, std::string const url) :
        name(name), url(url) {
    }

    /**
     * Default constructor for Page.
     */
    Page() = default;

    bool operator==(Page const& other) const {
        return name == other.name;
    }

    bool operator!=(Page const& other) const {
        return !(*this == other);
    }
};

#endif