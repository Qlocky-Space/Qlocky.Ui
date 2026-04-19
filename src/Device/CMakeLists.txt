declare_module(Device)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceInfoProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/DisplayServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/SystemPreferencesRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/LifecycleChangeRequestCommand.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/LifecycleChangeRequestCommand.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/DisplayService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/DisplayService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/SystemPreferencesRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/SystemPreferencesRepository.cpp

    ${CMAKE_CURRENT_LIST_DIR}/view/AboutViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AboutViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/NetInterfaceInfoViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/DevelopViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/DevelopViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/LifecycleStateType.h
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
    qlocky::Os
    qlocky::Persistence
    qlocky::Configuration
)
setup_module()
