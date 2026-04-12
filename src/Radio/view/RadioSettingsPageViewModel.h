#ifndef RADIO_SETTINGS_PAGE_VIEW_MODEL_H
#define RADIO_SETTINGS_PAGE_VIEW_MODEL_H

#include <Mediator.h>
#include <QObject>

#include "events/StationAddedEvent.h"
#include "events/StationRemovedEvent.h"
#include "StationRepositoryIfc.h"

/**
 * ViewModel for Radio settings page.
 * This class handles the logic for managing Radio settings.
 */
class RadioSettingsPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int stationCount READ stationCount NOTIFY stationCountChanged)
    Q_PROPERTY(bool downloading READ downloading NOTIFY downloadingChanged)

public:

    RadioSettingsPageViewModel(Mediator& mediator, StationRepositoryIfc& stationRepository);
    ~RadioSettingsPageViewModel() final = default;

    int stationCount() const {
        return m_stationCount;
    }

    bool downloading() const {
        return m_downloading;
    }

signals:

    void stationCountChanged();
    void downloadingChanged();

private:

    void setStationCount(int stationCount);

    void onStationAdded(StationAddedEvent const& event);
    void onStationRemoved(StationRemovedEvent const& event);

    int m_stationCount {0};
    bool m_downloading {false};
};

#endif