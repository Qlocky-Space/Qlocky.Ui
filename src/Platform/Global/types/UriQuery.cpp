#include "UriQuery.h"

#include <util/StringUtil.h>

namespace {
std::string anyToString(std::any const& value) {
    if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    else if (value.type() == typeid(char const*)) {
        return std::string(std::any_cast<char const*>(value));
    }
    else if (value.type() == typeid(char*)) {
        return std::string(std::any_cast<char*>(value));
    }
    else if (value.type() == typeid(int)) {
        return std::to_string(std::any_cast<int>(value));
    }
    else if (value.type() == typeid(unsigned int)) {
        return std::to_string(std::any_cast<unsigned int>(value));
    }
    else if (value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(value));
    }
    else if (value.type() == typeid(float)) {
        return std::to_string(std::any_cast<float>(value));
    }
    else if (value.type() == typeid(bool)) {
        return std::any_cast<bool>(value) ? "true" : "false";
    }

    return "<unsupported type>";
}

std::any stringToAny(std::type_info const& type, std::string const& value) {
    if (type == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    else if (type == typeid(char const*)) {
        return std::string(std::any_cast<char const*>(value));
    }
    else if (type == typeid(char*)) {
        return std::string(std::any_cast<char*>(value));
    }
    else if (type == typeid(int)) {
        return std::atoi(value.c_str());
    }
    else if (type == typeid(unsigned int)) {
        return static_cast<unsigned int>(std::atol(value.c_str()));
    }
    else if (type == typeid(double)) {
        return std::atof(value.c_str());
    }
    else if (type == typeid(float)) {
        return static_cast<float>(std::atof(value.c_str()));
    }
    else if (type == typeid(bool)) {
        return (value == "true") || value == "1";
    }

    return "<unsupported type>";
}
} // namespace

UriQuery::UriQuery(std::string const& str) :
    m_uri {str},
    m_params {} {
    parseParams(str, m_params);
}

UriQuery::UriQuery(Uri const& str) :
    m_uri {str},
    m_params {} {
}

bool UriQuery::isValid() {
    return m_uri.isValid();
}

Uri UriQuery::uri() const {
    return m_uri;
}

UriQuery::Params const& UriQuery::params() const {
    return m_params;
}

bool UriQuery::contains(std::string const& key) const {
    return m_params.count(key) > 0;
}

void UriQuery::parseParams(std::string const& str, Params& out) {
    auto paramsPos = str.find('?');
    if (paramsPos == std::string::npos) {
        return;
    }

    std::string paramsStr = str.substr(paramsPos + 1);
    StringUtil::trim(paramsStr);

    std::vector<std::string> const paramsPair {StringUtil::split(paramsStr, "&")};
    for (std::string const& pair : paramsPair) {
        std::vector<std::string> param {StringUtil::split(pair, "=")};
        if (param.size() != 2) {
            // Invalid param
            continue;
        }

        std::string key {param.at(0)};
        StringUtil::trim(key);

        std::string value {param.at(1)};
        StringUtil::trim(value);

        out[key] = value;
    }
}

std::any UriQuery::getParamInternal(std::string const& key, std::any const& defaultValue) const {
    if (!contains(key)) {
        return defaultValue;
    }

    return stringToAny(defaultValue.type(), m_params.at(key));
}

void UriQuery::addParamInternal(std::string const& key, std::any const& value) {
    m_params[key] = anyToString(value);
}

std::string UriQuery::toString() const {
    std::string str {m_uri.toString()};
    if (m_params.empty()) {
        return str;
    }

    str += "?";
    for (auto& param : m_params) {
        str += param.first + "=" + anyToString(param.second) + "&";
    }
    // remove last &
    str.erase(str.size() - 1);

    return str;
}

bool UriQuery::operator==(UriQuery const& query) const {
    return m_uri == query.m_uri && m_params == query.m_params;
}

bool UriQuery::operator!=(UriQuery const& query) const {
    return !(*this == query);
}
