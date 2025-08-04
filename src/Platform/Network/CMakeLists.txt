declare_module(Network)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/ConnectionStatusEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/WifiStatusEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/NetworkScanResultEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/CommunicationStatusEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkProfile.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkProfileEntity.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkStateType.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkStateType.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkProfileMapper.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkStateMachine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkStateMachine.h

    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiSettingsPageViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiSettingsPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiNetworkViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiNetworkViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiNetworkListModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/WiFiNetworkListModel.cpp
)

set_source_files_properties(qml/NetworkIconUtil.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)


set(MODULE_LINK
    qlocky::Os
    qlocky::Ui
    qlocky::Persistence
    qlocky::Configuration

    nlohmann_json::nlohmann_json
)

set(MODULE_QML_SRC
    qml/WiFiSettings.qml
    qml/internal/SettingKeyNetworkItem.qml
    qml/NetworkIconUtil.qml
)

setup_module()
