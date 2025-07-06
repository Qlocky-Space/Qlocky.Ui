#include "Uri.h"

namespace {

std::string extractScheme(std::string const& uri) {
    auto schemePos = uri.find(':');
    if (schemePos == std::string::npos) {
        return "";
    }

    return uri.substr(0, schemePos);
}

std::string extractPath(std::string const& uri) {
    auto paramsPos = uri.find('?');
    auto schemePos = uri.find(':');

    auto pathPos = (schemePos != std::string::npos) ? (schemePos + 3) : 0;
    size_t pathN = (paramsPos != std::string::npos) ? (paramsPos - pathPos) : std::string::npos;

    return uri.substr(pathPos, pathN);
}

} // namespace

Uri::Uri(std::string const& str) :
    m_scheme {extractScheme(str)},
    m_path {extractPath(str)} {
}

Uri::Uri(QString& str) :
    Uri {str.toStdString()} {
}

bool Uri::isValid() const {
    if (m_scheme.empty()) {
        return false;
    }

    if (m_path.empty()) {
        return false;
    }

    return true;
}

Uri::Scheme Uri::scheme() const {
    return m_scheme;
}

void Uri::setScheme(Scheme const& scheme) {
    m_scheme = scheme;
}

std::string Uri::path() const {
    return m_path;
}

std::string Uri::toString() const {
    return m_scheme + "://" + m_path;
}