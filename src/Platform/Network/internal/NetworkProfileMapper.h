#ifndef NETWORK_PROFILE_MAPPER_H
#define NETWORK_PROFILE_MAPPER_H

#include <memory>
#include <string>

#include "NetworkInfo.h"
#include "NetworkProfileEntity.h"
#include "NetworkProfileNew.h"

/**
 * NetworkProfileMapper provides conversion between NetworkProfileNew and NetworkProfileEntity.
 *
 * This mapper is designed to be generic and robust against new attributes.
 * It uses explicit field mapping and, where possible, delegates to getter/setter methods.
 * When new attributes are added to either model, only this file needs to be updated.
 */
class NetworkProfileMapper {
public:

    /**
     * Converts a NetworkProfileNew to a NetworkProfileEntity.
     * @param profile The network profile new to convert.
     * @return  The corresponding NetworkProfileEntity.
     */
    static NetworkProfileEntity toEntity(NetworkProfileNew const& profile) {
        return NetworkProfileEntity {
            0,
            profile.Ssid,
            profile.Psk,
            profile.SecurityType,
            profile.AutoConnect};
    }

    static NetworkInfo toNetworkInfo(NetworkProfileEntity const& profile) {
        return NetworkInfo {
            profile.ssid,
            profile.psk,
            profile.securityType};
    }
};

#endif