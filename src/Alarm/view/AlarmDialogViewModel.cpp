#include "AlarmDialogViewModel.h"

#include <QTimeZone>

#include "AlarmEntity.h"
#include "internal/AlarmMapper.h"

namespace {

static uint32_t defaultDueTime() {
    QDateTime now = QDateTime::currentDateTime(QTimeZone::utc());
    return now.time().msecsSinceStartOfDay() / 1000;
}

} // namespace

AlarmDialogViewModel::AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository, TimeFormatter& timeFormatter) :
    m_alarmRepository {alarmRepository},
    m_timeFormatter {timeFormatter},
    m_item {0U} {
}

void AlarmDialogViewModel::loadAlarm(int32_t const alarmId) {
    uint32_t const localDueTime {m_timeFormatter.toLocalDateTime(defaultDueTime()).time().msecsSinceStartOfDay() / 1000U};

    std::unique_ptr<AlarmItemViewModel> pItem {std::make_unique<AlarmItemViewModel>(alarmId)};
    pItem->setDisplayName("Alarm");
    pItem->setState(true);
    pItem->setDueTime(localDueTime);

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
    alarmEntity.id = m_item.getAlarmId() != 0 ? m_item.getAlarmId() : QDateTime::currentDateTime(QTimeZone::utc()).toSecsSinceEpoch();

    m_alarmRepository.addAlarm(alarmEntity);
}
