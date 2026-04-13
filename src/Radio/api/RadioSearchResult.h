#ifndef SRC_RADIO_API_RADIO_SEARCH_RESULT_H
#define SRC_RADIO_API_RADIO_SEARCH_RESULT_H

#include <cstdint>
#include <string>

#include "RadioEntity.h"

/**
 * Provider-specific metadata shown for one radio search result.
 */
struct RadioSearchResult {
    RadioEntity radio;
    std::string url;
    uint32_t votes {0};
    std::string favicon;
    std::string language;
};

#endif // SRC_RADIO_API_RADIO_SEARCH_RESULT_H
