#include "StationListModel.h"

#include <algorithm>

namespace {

QStringList toStringList(std::string const& value) {
    QStringList const values {QString::fromStdString(value).split(',', Qt::SkipEmptyParts)};
    QStringList normalizedValues {};

    for (QString const& item : values) {
        QString const trimmed {item.trimmed()};
        if (!trimmed.isEmpty()) {
            normalizedValues.push_back(trimmed);
        }
    }

    return normalizedValues;
}

void assignStation(StationViewModel& station, StationEntity const& entity) {
    station.setName(QString::fromStdString(entity.name).trimmed());
    station.setUrl(QString::fromStdString(entity.url).trimmed());
    station.setFavicon(QString::fromStdString(entity.favicon).trimmed());
    station.setTags(toStringList(entity.tags));
    station.setLanguage(toStringList(entity.language));
    station.setCountryCode(QString::fromStdString(entity.countryCode).trimmed());
    station.setVotes(entity.votes);
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
    QHash<int, QByteArray> roles {};
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

void StationListModel::addStation(StationEntity const& stationEntity) {
    beginInsertRows(QModelIndex(), m_stations.size(), m_stations.size());

    StationViewModel* station = new StationViewModel {stationEntity.id};
    assignStation(*station, stationEntity);
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

void StationListModel::updateStation(StationEntity const& stationEntity) {
    auto it = findStationById(stationEntity.id);

    if (it == m_stations.end()) {
        addStation(stationEntity);
        return;
    }

    assignStation(*(*it), stationEntity);

    int const index = std::distance(m_stations.begin(), it);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
}

void StationListModel::removeStation(Uuid const& id) {
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

QVector<StationViewModel*>::iterator StationListModel::findStationById(Uuid const& id) {
    QString const stationId {QString::fromStdString(id.toString())};
    return std::find_if(m_stations.begin(), m_stations.end(), [&stationId](StationViewModel* station) {
        return station->stationId() == stationId;
    });
}
