#ifndef NETWORK_PROFILE_MAPPER_H
#define NETWORK_PROFILE_MAPPER_H

#include <memory>
#include <string>

#include "NetworkInfo.h"
#include "NetworkProfileEntity.h"
#include "NetworkProfileNew.h"
#include "PskEncryption.h"
#include "util/StringUtil.h"

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
        PskEncryption::Psk psk {PskEncryption::encrypt(profile.Psk, profile.Ssid)};

        return NetworkProfileEntity {
            0,
            profile.Ssid,
            StringUtil::bytesToHexDump(psk.data(), psk.size()),
            profile.SecurityType,
            profile.AutoConnect};
    }

    /**
     * Converts a NetworkProfileEntity to a NetworkProfileNew.
     * @param entity The network profile entity to convert.
     * @return  The corresponding NetworkProfileNew.
     */
    static NetworkInfo toNetworkInfo(NetworkProfileEntity const& profile) {
        NetworkInfo info {};
        info.ssid = profile.ssid;
        if (profile.psk.length() >= 64) {
            info.passphrase = StringUtil::hexDumpToBytes(profile.psk);
        }
        else {
            info.passphrase = profile.psk; // Assume it's not encrypted
        }
        info.keyMgmnt = profile.securityType;
        return info;
    }

private:
};

#endif