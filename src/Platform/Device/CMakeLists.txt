declare_module(Device)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceInfoProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmPreferencesRepositoryIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmPreferencesRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmPreferencesRepository.cpp

    ${CMAKE_CURRENT_LIST_DIR}/view/AboutViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AboutViewModel.h
)

set(MODULE_QML_SRC
    qml/internal/SettingHostnameItem.qml
    qml/About.qml
    qml/Develop.qml
)

set(MODULE_QML_RESOURCES
    resources/DeviceFrame.png
)

set(MODULE_INCLUDE
    ${CMAKE_BINARY_DIR}
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Persistence
    qlocky::Configuration
)
setup_module()
