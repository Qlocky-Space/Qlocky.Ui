#ifndef NAVIGATION_URI_QUERY_H
#define NAVIGATION_URI_QUERY_H

#include <any>
#include <map>
#include <string>

#include "Uri.h"

class UriQuery {
public:

    using Params = std::map<std::string, std::string>;

    UriQuery() = default;
    explicit UriQuery(std::string const& str);
    explicit UriQuery(Uri const& str);

    bool isValid();

    Params const& params() const;
    bool contains(std::string const& key) const;
    template<class T>
    T getParam(std::string const& key, T const& defaultValue = T {}) const {
        return std::any_cast<T>(getParamInternal(key, defaultValue));
    }

    template<class T>
    void addParam(std::string const& key, T const& value) {
        addParamInternal(key, value);
    }

    std::string toString() const;

private:

    static void parseParams(std::string const& str, Params& out);

    std::any getParamInternal(std::string const& key, std::any const& defaultValue) const;
    void addParamInternal(std::string const& key, std::any const& value);

    Uri m_uri;
    Params m_params;
};

#endif