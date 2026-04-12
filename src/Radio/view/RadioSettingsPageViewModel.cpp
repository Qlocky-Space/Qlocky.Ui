#include "RadioSettingsPageViewModel.h"

RadioSettingsPageViewModel::RadioSettingsPageViewModel(Mediator& mediator, StationRepositoryIfc& stationRepository) :
    QObject {nullptr} {
    setStationCount(static_cast<int>(stationRepository.getAllStations().size()));
    mediator.subscribe<StationAddedEvent>(this, &RadioSettingsPageViewModel::onStationAdded);
    mediator.subscribe<StationRemovedEvent>(this, &RadioSettingsPageViewModel::onStationRemoved);
}

void RadioSettingsPageViewModel::setStationCount(int stationCount) {
    if (m_stationCount == stationCount) {
        return;
    }

    m_stationCount = stationCount;
    emit stationCountChanged();
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
