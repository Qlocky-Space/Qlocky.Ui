#ifndef SRC_RADIO_API_STATION_ENTITY_H
#define SRC_RADIO_API_STATION_ENTITY_H

#include <cstdint>
#include <string>
#include <types/Uuid.h>

/**
 * Represents the stored station entity used inside the Radio module.
 */
using StationId = Uuid;

struct StationEntity {
    StationId id;
    std::string name;
    std::string url;
    std::string favicon;
    std::string tags;
    std::string language;
    std::string countryCode;
    uint32_t votes;
};

#endif // SRC_RADIO_API_STATION_ENTITY_H