#ifndef NETWORK_PROFILE_ENTITY_H
#define NETWORK_PROFILE_ENTITY_H

#include <cstdint>
#include <nlohmann/json.hpp>
#include <string>

/**
 * Represents a network profile entity.
 */
using ProfileId = uint32_t;

struct NetworkProfileEntity {
    ProfileId id;
    std::string ssid;
    std::string psk;
    std::string securityType;
    bool autoConnect;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(NetworkProfileEntity, id, ssid, psk, securityType, autoConnect)
};

#endif
