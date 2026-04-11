#ifndef RADIO_SETTINGS_PAGE_VIEW_MODEL_H
#define RADIO_SETTINGS_PAGE_VIEW_MODEL_H

#include <Mediator.h>
#include <QObject>

#include "events/StationAddedEvent.h"
#include "events/StationRemovedEvent.h"
#include "events/StationUpdatedEvent.h"
#include "StationListModel.h"

/**
 * ViewModel for Radio settings page.
 * This class handles the logic for managing Radio settings.
 */
class RadioSettingsPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* radios READ radios CONSTANT)

public:

    explicit RadioSettingsPageViewModel(Mediator& mediator, StationListModel& stationListModel);
    ~RadioSettingsPageViewModel() final = default;

    /**
     * Gets the list of radios.
     * @return The model containing the list of radios.
     */
    QAbstractListModel* radios() {
        return &m_stationListModel;
    }

signals:

private:

    void onStationAdded(StationAddedEvent const& event);
    void onStationRemoved(StationRemovedEvent const& event);
    void onStationUpdated(StationUpdatedEvent const& event);

    Mediator& m_mediator;
    StationListModel& m_stationListModel;
};

#endif