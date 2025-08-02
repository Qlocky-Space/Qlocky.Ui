declare_module(Configuration)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationRegistryIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/ConfigurationRegistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/ConfigurationRegistry.h

    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingItemViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingItemViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingListModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingListModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingListProxyModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingListProxyModel.h

)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Persistence

    ng-log::ng-log
)

set(MODULE_QML_SRC
    qml/internal/SettingMenu.qml
    qml/internal/SettingMenuHeader.qml
    qml/internal/SettingMenuItem.qml
    qml/SettingPage.qml
)


setup_module()
