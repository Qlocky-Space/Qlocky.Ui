#include "StationViewModel.h"

StationViewModel::StationViewModel(Uuid const& stationId) :
    QObject {nullptr},
    m_stationId {stationId} {
}

void StationViewModel::setName(QString const& name) {
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void StationViewModel::setUrl(QString const& url) {
    if (m_url != url) {
        m_url = url;
        emit urlChanged();
    }
}

void StationViewModel::setFavicon(QString const& favicon) {
    if (m_favicon != favicon) {
        m_favicon = favicon;
        emit faviconChanged();
    }
}

void StationViewModel::setTags(QStringList const& tags) {
    if (m_tags != tags) {
        m_tags = tags;
        emit tagsChanged();
    }
}

void StationViewModel::setLanguage(QStringList const& language) {
    if (m_language != language) {
        m_language = language;
        emit languageChanged();
    }
}

void StationViewModel::setCountryCode(QString const& countryCode) {
    if (m_countryCode != countryCode) {
        m_countryCode = countryCode;
        emit countryCodeChanged();
    }
}

void StationViewModel::setVotes(uint32_t votes) {
    if (m_votes != votes) {
        m_votes = votes;
        emit votesChanged();
    }
}
