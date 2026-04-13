#include "RadioSettingsPageViewModel.h"

#include "RadioRepositoryIfc.h"

RadioSettingsPageViewModel::RadioSettingsPageViewModel(Mediator& mediator, RadioRepositoryIfc& radioRepository) :
    QObject {nullptr} {
    setStationCount(static_cast<int>(radioRepository.getFavorites().size()));
    mediator.subscribe<RadioFavoriteAddedEvent>(this, &RadioSettingsPageViewModel::onFavoriteAdded);
    mediator.subscribe<RadioFavoriteRemovedEvent>(this, &RadioSettingsPageViewModel::onFavoriteRemoved);
}

void RadioSettingsPageViewModel::setStationCount(int stationCount) {
    if (m_stationCount == stationCount) {
        return;
    }

    m_stationCount = stationCount;
    emit stationCountChanged();
}

void RadioSettingsPageViewModel::onFavoriteAdded(RadioFavoriteAddedEvent const& event) {
    Q_UNUSED(event);
    setStationCount(m_stationCount + 1);
}

void RadioSettingsPageViewModel::onFavoriteRemoved(RadioFavoriteRemovedEvent const& event) {
    Q_UNUSED(event);
    if (m_stationCount == 0) {
        return;
    }

    setStationCount(m_stationCount - 1);
}
