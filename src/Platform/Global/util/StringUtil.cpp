#include "StringUtil.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

void StringUtil::trim(std::string& str) {
    StringUtil::ltrim(str);
    StringUtil::rtrim(str);
}

std::vector<std::string> StringUtil::split(std::string const& str, std::string const& delimiter) {
    std::vector<std::string> tokens {};

    std::size_t current, previous {0};
    current = str.find(delimiter);
    std::size_t delimLen = delimiter.length();

    while (current != std::string::npos) {
        tokens.push_back(str.substr(previous, current - previous));
        previous = current + delimLen;
        current = str.find(delimiter, previous);
    }
    tokens.push_back(str.substr(previous, current - previous));

    return tokens;
}

std::vector<uint8_t> StringUtil::hexDumpToBytes(std::string const& hex) {
    if (hex.length() % 2 != 0) {
        return {};
    }

    std::vector<uint8_t> bytes;
    bytes.reserve(hex.length() / 2);

    auto hexCharToInt = [](char c) -> uint8_t {
        if (c >= '0' && c <= '9') {
            return c - '0';
        }
        if (c >= 'a' && c <= 'f') {
            return c - 'a' + 10;
        }
        if (c >= 'A' && c <= 'F') {
            return c - 'A' + 10;
        }
        return {};
    };

    for (size_t i = 0; i < hex.length(); i += 2) {
        uint8_t high = hexCharToInt(hex[i]);
        uint8_t low = hexCharToInt(hex[i + 1]);
        bytes.push_back((high << 4) | low);
    }

    return bytes;
}

std::string StringUtil::bytesToHexDump(uint8_t const* data, std::size_t size) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (std::size_t i {0}; i < size; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

void StringUtil::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void StringUtil::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(),
        s.end());
}
