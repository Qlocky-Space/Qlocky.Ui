#ifndef PSK_ENCRYPTION_H
#define PSK_ENCRYPTION_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * PskEncryption class provides functionality to encrypt passwords
 * using PBKDF2-HMAC-SHA1 algorithm.
 */
class PskEncryption {
public:

    /**
     * Type alias for the PSK (Pre-Shared Key)
     */
    using Psk = std::vector<uint8_t>;

    /**
     * Encrypts a password using PBKDF2-HMAC-SHA1.
     * @param password The password to encrypt.
     * @param ssid The SSID to use as salt.
     * @return The encrypted password.
     */
    static Psk encrypt(std::string const& password, std::string const& ssid);

    PskEncryption() = delete;
    PskEncryption(PskEncryption const&) = delete;
    PskEncryption& operator=(PskEncryption const&) = delete;
    PskEncryption(PskEncryption&&) = delete;
    PskEncryption& operator=(PskEncryption&&) = delete;
    ~PskEncryption() = delete;
};

#endif // PSK_ENCRYPTION_H