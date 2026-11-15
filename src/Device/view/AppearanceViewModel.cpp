#include "AppearanceViewModel.h"

AppearanceViewModel::AppearanceViewModel(Mediator& mediator, SystemPreferencesRepositoryIfc& repository) :
    m_repository {repository} {
}

void AppearanceViewModel::changeTimeFormat(bool is24HoursFormat) {
    m_repository.setTimeFormat(is24HoursFormat);
    emit timeFormatChanged();
}

bool AppearanceViewModel::getTimeFormatBoolean() const {
    return m_repository.isTimeFormat24Hour();
}