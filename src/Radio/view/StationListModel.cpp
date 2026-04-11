#include "StationListModel.h"

#include <algorithm>

namespace {

QStringList toStringList(std::string const& value) {
    return QString::fromStdString(value).split(',', Qt::SkipEmptyParts);
}

void assignProfile(StationViewModel& station, StationProfile const& profile) {
    station.setName(QString::fromStdString(profile.Name));
    station.setUrl(QString::fromStdString(profile.Url));
    station.setFavicon(QString::fromStdString(profile.Favicon));
    station.setTags(toStringList(profile.Tags));
    station.setLanguage(toStringList(profile.Language));
    station.setCountryCode(QString::fromStdString(profile.CountryCode));
    station.setVotes(static_cast<int>(profile.Votes));
}

} // namespace

StationListModel::StationListModel() :
    QAbstractListModel {nullptr} {
}

StationListModel::~StationListModel() {
    clearStations();
}

int StationListModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
    return m_stations.size();
}

QVariant StationListModel::data(QModelIndex const& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_stations.size()) {
        return {};
    }

    StationViewModel* station = m_stations.at(index.row());
    switch (role) {
        case StationId:
            return station->stationId();
        case Language:
            return station->language();
        case Country:
            return station->countryCode();
        case Votes:
            return station->votes();
        case Name:
            return station->name();
        case Url:
            return station->url();
        case Favicon:
            return station->favicon();
        case Tags:
            return station->tags();
        default:
            return {};
    }
}

QHash<int, QByteArray> StationListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[StationId] = "stationId";
    roles[Language] = "language";
    roles[Country] = "countryCode";
    roles[Votes] = "votes";
    roles[Name] = "name";
    roles[Url] = "url";
    roles[Favicon] = "favicon";
    roles[Tags] = "tags";
    return roles;
}

void StationListModel::addStation(StationProfile const& profile) {
    beginInsertRows(QModelIndex(), m_stations.size(), m_stations.size());

    StationViewModel* station = new StationViewModel {profile.StationId};
    assignProfile(*station, profile);
    m_stations.append(station);

    endInsertRows();
}

void StationListModel::removeStation(int index) {
    if (index < 0 || index >= m_stations.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    delete m_stations.takeAt(index);
    endRemoveRows();
}

void StationListModel::updateStation(StationProfile const& profile) {
    auto it = findStationById(profile.StationId.toString());

    if (it == m_stations.end()) {
        addStation(profile);
        return;
    }

    assignProfile(*(*it), profile);

    int const index = std::distance(m_stations.begin(), it);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void StationListModel::removeStation(std::string const& id) {
    auto it = findStationById(id);

    if (it != m_stations.end()) {
        removeStation(std::distance(m_stations.begin(), it));
    }
}

void StationListModel::clearStations() {
    beginResetModel();
    qDeleteAll(m_stations);
    m_stations.clear();
    endResetModel();
}

QVector<StationViewModel*>::iterator StationListModel::findStationById(std::string const& id) {
    return std::find_if(m_stations.begin(), m_stations.end(), [&id](StationViewModel* station) {
        return station->stationId() == QString::fromStdString(id);
    });
}
