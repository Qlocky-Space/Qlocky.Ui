#include "RadioSettingsPageViewModel.h"

#include "internal/StationMapper.h"

RadioSettingsPageViewModel::RadioSettingsPageViewModel(Mediator& mediator, StationListModel& stationListModel) :
    QObject {nullptr},
    m_mediator {mediator},
    m_stationListModel {stationListModel} {
    mediator.subscribe<StationAddedEvent>(this, &RadioSettingsPageViewModel::onStationAdded);
    mediator.subscribe<StationRemovedEvent>(this, &RadioSettingsPageViewModel::onStationRemoved);
    mediator.subscribe<StationUpdatedEvent>(this, &RadioSettingsPageViewModel::onStationUpdated);
}

void RadioSettingsPageViewModel::onStationAdded(StationAddedEvent const& event) {
    m_stationListModel.updateStation(StationMapper::toProfile(event.station));
}

void RadioSettingsPageViewModel::onStationRemoved(StationRemovedEvent const& event) {
    m_stationListModel.removeStation(event.stationId.toString());
}

void RadioSettingsPageViewModel::onStationUpdated(StationUpdatedEvent const& event) {
    m_stationListModel.updateStation(StationMapper::toProfile(event.station));
}
