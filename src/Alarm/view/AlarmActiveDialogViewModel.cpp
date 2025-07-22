#include "AlarmActiveDialogViewModel.h"

#include <QTimeZone>

#include "AlarmEntity.h"
#include "internal/AlarmMapper.h"

namespace {

} // namespace

AlarmActiveDialogViewModel::AlarmActiveDialogViewModel(AlarmRepositoryIfc& alarmRepository) :
    m_alarmRepository {alarmRepository},
    m_item {0U} {
}

void AlarmActiveDialogViewModel::loadAlarm(uint32_t const alarmId) {
    for (auto const& alarm : m_alarmRepository.alarms()) {
        if (alarm.id == alarmId) {
            m_item.updateFrom(*AlarmMapper::toViewModel(alarm));
            break;
        }
    }
}

void AlarmActiveDialogViewModel::snooze() {
    // TODO
}

void AlarmActiveDialogViewModel::dismiss() {
    m_alarmRepository.setAlarmState(m_item.getAlarmId(), m_item.isRepeated());
}
