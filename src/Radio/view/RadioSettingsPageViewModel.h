#ifndef RADIO_SETTINGS_PAGE_VIEW_MODEL_H
#define RADIO_SETTINGS_PAGE_VIEW_MODEL_H

#include <Mediator.h>
#include <QObject>

#include "events/StationAddedEvent.h"
#include "events/StationRemovedEvent.h"

/**
 * ViewModel for Radio settings page.
 * This class handles the logic for managing Radio settings.
 */
class RadioSettingsPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int stationCount READ stationCount NOTIFY stationCountChanged)

public:

    explicit RadioSettingsPageViewModel(Mediator& mediator);
    ~RadioSettingsPageViewModel() final = default;

    int stationCount() const {
        return m_stationCount;
    }

signals:

    void stationCountChanged();

private:

    void setStationCount(int stationCount);

    void onStationAdded(StationAddedEvent const& event);
    void onStationRemoved(StationRemovedEvent const& event);

    Mediator& m_mediator;
    int m_stationCount {0};
};

#endif