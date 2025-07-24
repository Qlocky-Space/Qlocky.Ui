#include "StatusBarViewModel.h"

StatusBarViewModel::StatusBarViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_networkStrength {-1},
    m_title {"Qlocky"},
    m_airplaneMode {false} {
}
