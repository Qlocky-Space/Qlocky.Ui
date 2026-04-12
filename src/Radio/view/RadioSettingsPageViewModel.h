#ifndef RADIO_SETTINGS_PAGE_VIEW_MODEL_H
#define RADIO_SETTINGS_PAGE_VIEW_MODEL_H

#include <Mediator.h>
#include <QObject>

#include "events/RadioFavoriteAddedEvent.h"
#include "events/RadioFavoriteRemovedEvent.h"

class RadioRepositoryIfc;

/**
 * ViewModel for Radio settings page.
 * This class handles the logic for managing Radio settings.
 */
class RadioSettingsPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int stationCount READ stationCount NOTIFY stationCountChanged)
    Q_PROPERTY(bool downloading READ downloading NOTIFY downloadingChanged)

public:

    RadioSettingsPageViewModel(Mediator& mediator, RadioRepositoryIfc& radioRepository);
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

    void onFavoriteAdded(RadioFavoriteAddedEvent const& event);
    void onFavoriteRemoved(RadioFavoriteRemovedEvent const& event);

    int m_stationCount {0};
    bool m_downloading {false};
};

#endif