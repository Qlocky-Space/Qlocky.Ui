#ifndef GLOBAL_STRING_UTIL_H
#define GLOBAL_STRING_UTIL_H

#include <cstdint>
#include <string>
#include <vector>

class StringUtil {
public:

    /**
     * @brief Removes leading and trailing whitespace from the input string.
     * @param str The input string.
     * @return A copy of the trimmed string.
     */
    static void trim(std::string& str);

    /**
     * @brief Splits a string by a single character delimiter.
     * @param str The input string to split.
     * @param delimiter The character to split by.
     * @return A vector of string tokens.
     */
    static std::vector<std::string> split(std::string const& str, std::string const& delimiter);

    /**
     * @brief Converts a hexadecimal string to a vector of bytes.
     * @param hex The hexadecimal string to convert.
     * @return A vector of bytes representing the hexadecimal string.
     * If the string length is not even, an empty vector is returned.
     */
    static std::vector<uint8_t> hexDumpToBytes(std::string const& hex);

    /**
     * @brief Converts a byte array to a hexadecimal string.
     * @param data Pointer to the byte array.
     * @param size Number of bytes in the array.
     * @return Hexadecimal string representation.
     */
    static std::string bytesToHexDump(uint8_t const* data, std::size_t size);
    static std::string bytesToHexDump(std::vector<uint8_t> const& data) {
        return bytesToHexDump(data.data(), data.size());
    }

    StringUtil() = delete;

private:

    static void ltrim(std::string& s);
    static void rtrim(std::string& s);
};

#endif // STRING_UTIL_H
