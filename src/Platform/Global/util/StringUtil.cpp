#include "StringUtil.h"

#include <algorithm>

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
