#ifndef STATION_VIEW_MODEL_H
#define STATION_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <types/Uuid.h>

/**
 * StationViewModel represents a radio station with properties such as name, URL, and votes.
 */
class StationViewModel final : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString stationId READ stationId CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString favicon READ favicon WRITE setFavicon NOTIFY faviconChanged)
    Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)
    Q_PROPERTY(QStringList language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString countryCode READ countryCode WRITE setCountryCode NOTIFY countryCodeChanged)
    Q_PROPERTY(uint32_t votes READ votes WRITE setVotes NOTIFY votesChanged)

public:

    explicit StationViewModel(Uuid const& stationId);
    ~StationViewModel() final = default;

    /**
     * Gets the globally unique identifier of the station.
     * @return The station identifier.
     */
    QString stationId() const {
        return QString::fromStdString(m_stationId.toString());
    }

    /**
     * Gets the name of the radio station.
     * @return The name of the station.
     */
    QString name() const {
        return m_name;
    }

    /**
     * Sets the name of the radio station.
     * @param name The name to set.
     */
    void setName(QString const& name);

    /**
     * Gets the URL of the radio station.
     * @return The URL of the station.
     */
    QString url() const {
        return m_url;
    }

    /**
     * Sets the URL of the radio station.
     * @param url The URL to set.
     */
    void setUrl(QString const& url);

    /**
     * Gets the favicon URL of the radio station.
     * @return The favicon URL of the station.
     */
    QString favicon() const {
        return m_favicon;
    }

    /**
     * Sets the favicon URL of the radio station.
     * @param favicon The favicon URL to set.
     */
    void setFavicon(QString const& favicon);

    /**
     * Gets the station tags.
     * @return The comma separated tags of the station.
     */
    QStringList tags() const {
        return m_tags;
    }

    /**
     * Sets the station tags.
     * @param tags The comma separated tags to set.
     */
    void setTags(QStringList const& tags);

    /**
     * Gets the station language information.
     * @return The comma separated station languages.
     */
    QStringList language() const {
        return m_language;
    }

    /**
     * Sets the station language information.
     * @param language The comma separated station languages to set.
     */
    void setLanguage(QStringList const& language);

    /**
     * Gets the station country code.
     * @return The ISO 3166-1 alpha-2 country code.
     */
    QString countryCode() const {
        return m_countryCode;
    }

    /**
     * Sets the station country code.
     * @param countryCode The ISO 3166-1 alpha-2 country code to set.
     */
    void setCountryCode(QString const& countryCode);

    /**
     * Gets the station vote count.
     * @return The number of votes for the station.
     */
    uint32_t votes() const {
        return m_votes;
    }

    /**
     * Sets the station vote count.
     * @param votes The number of votes to set.
     */
    void setVotes(uint32_t votes);

signals:
    void stationIdChanged();
    void nameChanged();
    void urlChanged();
    void faviconChanged();
    void tagsChanged();
    void languageChanged();
    void countryCodeChanged();
    void votesChanged();

private:

    Uuid m_stationId;
    QString m_name {};
    QString m_url {};
    QString m_favicon {};
    QStringList m_tags {};
    QStringList m_language {};
    QString m_countryCode {};
    uint32_t m_votes {0};
};

#endif