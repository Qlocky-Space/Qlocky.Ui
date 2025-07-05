

#include "SettingPageViewModel.h"

SettingPageViewModel::SettingPageViewModel(NavigateBackCommand& navigateBackCommand) :
    QObject {nullptr},
    m_navigateBackCommand {navigateBackCommand} {
}
