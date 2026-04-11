#ifndef SRC_RADIO_VIEW_STATION_LIST_MODEL_H
#define SRC_RADIO_VIEW_STATION_LIST_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "StationProfile.h"
#include "StationViewModel.h"
#include "types/Uri.h"

/**
 * StationListModel is a model that holds a list of stations.
 * It provides methods to manage the list and notify views of changes.
 */
class StationListModel : public QAbstractListModel {
    Q_OBJECT

public:

    /**
     * @brief Roles for the station model.
     * These roles are used to access specific properties of the stations.
     * @note https://de1.api.radio-browser.info/#Struct_station
     */
    enum Roles {
        StationId = Qt::UserRole + 1,
        Language,
        Country,
        Votes,
        Name,
        Url,
        Favicon,
        Tags,
    };

    explicit StationListModel();
    ~StationListModel() final;

    /**
     * @see QAbstractListModel::rowCount
     */
    int rowCount(QModelIndex const& parent = QModelIndex()) const final;

    /**
     * @see QAbstractListModel::data
     */
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const final;

    /**
     * @see QAbstractListModel::roleNames
     */
    QHash<int, QByteArray> roleNames() const final;

    /**
     * Adds a station to the model.
     * @param station The station to add.
     */
    void addStation(StationProfile const& profile);

    /**
     * Updates an existing station in the model.
     * @param station The station to update.
     */
    void updateStation(StationProfile const& profile);

    /**
     * Removes a station from the model.
     * @param station The station to remove.
     */
    void removeStation(std::string const& id);

    /**
     * Clears all stations from the model.
     */
    void clearStations();

private:

    void removeStation(int index);

    QVector<StationViewModel*>::iterator findStationById(std::string const& id);

    QVector<StationViewModel*> m_stations;
};

#endif // SRC_RADIO_VIEW_STATION_LIST_MODEL_H