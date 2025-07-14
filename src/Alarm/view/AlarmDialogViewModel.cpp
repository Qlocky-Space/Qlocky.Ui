#include "AlarmDialogViewModel.h"

#include "AlarmEntity.h"

AlarmDialogViewModel::AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository) :
    m_alarmRepository(alarmRepository) {
}

void AlarmDialogViewModel::save() {
    // TODO create based on properties
    AlarmEntity alarmEntity;
    alarmEntity.id = QDateTime::currentDateTime().toSecsSinceEpoch();
    alarmEntity.name = "Test Alarm";
    alarmEntity.dueTime = QDateTime::currentDateTime().toSecsSinceEpoch();
    alarmEntity.isActive = true;

    m_alarmRepository.addAlarm(alarmEntity);
}
