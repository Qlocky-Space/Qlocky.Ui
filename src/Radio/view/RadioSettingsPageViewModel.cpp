#include "RadioSettingsPageViewModel.h"

#include <QMetaObject>

RadioSettingsPageViewModel::RadioSettingsPageViewModel(Mediator& mediator, StationServiceIfc& stationService) :
    QObject {nullptr},
    m_stationService {stationService} {
    mediator.subscribe<StationAddedEvent>(this, &RadioSettingsPageViewModel::onStationAdded);
    mediator.subscribe<StationRemovedEvent>(this, &RadioSettingsPageViewModel::onStationRemoved);
    mediator.subscribe<StationServiceStateChangedEvent>(this, &RadioSettingsPageViewModel::onStationServiceStateChanged);
}

void RadioSettingsPageViewModel::updateStations() {
    StationFilter filter {}; // TODO: Expose filter options in the UI
    filter.country = "CH";
    m_stationService.updateStations(filter);
}

void RadioSettingsPageViewModel::setStationCount(int stationCount) {
    if (m_stationCount == stationCount) {
        return;
    }

    m_stationCount = stationCount;
    emit stationCountChanged();
}

void RadioSettingsPageViewModel::setDownloading(bool downloading) {
    if (m_downloading == downloading) {
        return;
    }

    m_downloading = downloading;
    emit downloadingChanged();
}

void RadioSettingsPageViewModel::onStationAdded(StationAddedEvent const& event) {
    Q_UNUSED(event);
    setStationCount(m_stationCount + 1);
}

void RadioSettingsPageViewModel::onStationRemoved(StationRemovedEvent const& event) {
    Q_UNUSED(event);
    if (m_stationCount == 0) {
        return;
    }

    setStationCount(m_stationCount - 1);
}

void RadioSettingsPageViewModel::onStationServiceStateChanged(StationServiceStateChangedEvent const& event) {
    switch (event.state) {
        case StationServiceStateChangedEvent::State::Updating:
            setDownloading(true);
            break;
        case StationServiceStateChangedEvent::State::Canceled:
        case StationServiceStateChangedEvent::State::Finished:
            setDownloading(false);
            break;
    }
}
