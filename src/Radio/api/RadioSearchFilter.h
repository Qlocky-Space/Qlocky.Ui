#ifndef SRC_RADIO_API_RADIO_SEARCH_FILTER_H
#define SRC_RADIO_API_RADIO_SEARCH_FILTER_H

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

/**
 * Filter used by the radio service and radio source providers to search radios.
 */
struct RadioSearchFilter {
    std::string language {};
    std::string country {};
    std::vector<std::string> tags {};
    std::optional<std::string> name {};

    /**
     * @return True when the filter does not constrain any field.
     */
    bool isEmpty() const {
        auto const hasNonEmptyTag = std::any_of(tags.begin(), tags.end(), [](std::string const& tag) {
            return !tag.empty();
        });

        return language.empty() && country.empty() && !hasNonEmptyTag && (!name.has_value() || name->empty());
    }
};

#endif // SRC_RADIO_API_RADIO_SEARCH_FILTER_H