declare_module(Configuration)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/ConfigurationRegistryIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/ConfigurationRegistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/ConfigurationRegistry.h

    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.h
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Persistence

    # TODO to remove this dependency
    qlocky::Network
)

set(MODULE_QML_SRC
    qml/SettingPage.qml
)


setup_module()
