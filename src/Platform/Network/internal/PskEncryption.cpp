#include "PskEncryption.h"

#include <array>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <vector>

PskEncryption::Psk PskEncryption::encrypt(std::string const& password, std::string const& ssid) {
    constexpr uint32_t iterations = 4096;
    constexpr uint32_t keyLength = (256 / 8); // 256 bits = 32 bytes

    std::vector<uint8_t> saltBytes(ssid.begin(), ssid.end());

    std::array<uint8_t, keyLength> encryptedPsk {};

    // PBKDF2-HMAC-SHA1 for wpa_supplicant:
    //      passphrase: the Wi-Fi password (8–63 ASCII characters)
    //      SSID: the Wi-Fi network name (used as salt)
    //      iterations: 4096
    //      key length: 32 bytes

    PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), password.length(),
        saltBytes.data(), saltBytes.size(),
        iterations, keyLength, encryptedPsk.data());

    return Psk {encryptedPsk.begin(), encryptedPsk.end()};
}