#include "AlarmDialogViewModel.h"

#include <QTimeZone>

#include "AlarmEntity.h"
#include "internal/AlarmMapper.h"

AlarmDialogViewModel::AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository) :
    m_alarmRepository(alarmRepository),
    m_item {0U} {
}

void AlarmDialogViewModel::loadAlarm(int32_t const alarmId) {
    std::unique_ptr<AlarmItemViewModel> pItem {std::make_unique<AlarmItemViewModel>(alarmId)};
    pItem->setDisplayName("Alarm");
    pItem->setState(true);
    // TODO fix workaround, timezone shall be used
    pItem->setDueTime(QDateTime::currentDateTimeUtc().addSecs(2 * 3600));

    for (auto const& alarm : m_alarmRepository.alarms()) {
        if (alarm.id == alarmId) {
            pItem = AlarmMapper::toViewModel(alarm);
            break;
        }
    }

    m_item.updateFrom(*pItem);
}

void AlarmDialogViewModel::save() {
    AlarmEntity alarmEntity {AlarmMapper::toEntity(m_item)};
    // ensure alarm has unique id, when updated
    alarmEntity.id = m_item.getAlarmId() != 0 ? m_item.getAlarmId() : QDateTime::currentDateTime().toSecsSinceEpoch();

    m_alarmRepository.addAlarm(alarmEntity);
}
