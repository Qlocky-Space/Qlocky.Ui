#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <string_view>

/**
 * Represents a page in the navigation system.
 */
struct Page {
    std::string_view name; ///< The name of the page.
    std::string_view url;  ///< The URL associated with the page.

    /**
     * Constructs a Page with the given name and URL.
     * @param name The name of the page.
     * @param url The URL of the page.
     */
    constexpr Page(std::string_view const name, std::string_view const url) :
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

    // rule of five
    Page(Page const&) = default;
    Page(Page&&) = default;
    Page& operator=(Page&&) = default;

    // assignment operator
    Page& operator=(Page const& page) {
        name = page.name;
        url = page.url;
        return *this;
    }
};

#endif