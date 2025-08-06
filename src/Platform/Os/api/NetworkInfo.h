#ifndef OS_NETWORK_INFO_H
#define OS_NETWORK_INFO_H

#include <cinttypes>
#include <string>
#include <variant>
#include <vector>

/**
 * NetworkInfo represents the low level information about a network connection.
 */
struct NetworkInfo {
    std::string ssid;
    std::variant<std::string, std::vector<uint8_t>> passphrase;
    std::string keyMgmnt;

    /**
     * Checks if the passphrase is encrypted.
     * @return true if the passphrase is encrypted, false if it is a plain string
     */
    bool pskEncrypted() const {
        return !std::holds_alternative<std::string>(passphrase);
    }

    /**
     * Gets the passphrase as a string (Non-encrypted)
     * @return The passphrase as a string.
     * @throws std::bad_variant_access if the passphrase is not a string.
     */
    std::string psk() const {
        return std::get<std::string>(passphrase);
    }

    /**
     * Gets the passphrase as a vector of bytes (Encrypted)
     * @return The passphrase as a vector of bytes.
     * @throws std::bad_variant_access if the passphrase is not a vector of bytes.
     */
    std::vector<uint8_t> pskBytes() const {
        return std::get<std::vector<uint8_t>>(passphrase);
    }
};

#endif