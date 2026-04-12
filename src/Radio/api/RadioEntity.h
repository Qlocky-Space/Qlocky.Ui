#ifndef SRC_RADIO_API_RADIO_ENTITY_H
#define SRC_RADIO_API_RADIO_ENTITY_H

#include <string>

using RadioId = std::string;

inline RadioId makeRadioId(std::string const& provider, std::string const& providerRadioId) {
    return provider + ":" + providerRadioId;
}

/**
 * Provider-independent radio selection entity.
 */
struct RadioEntity {
    RadioId id;
    std::string name;
    std::string provider;
    std::string radioId;
    std::string url;
};

#endif // SRC_RADIO_API_RADIO_ENTITY_H
