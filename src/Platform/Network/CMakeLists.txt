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

    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkProfileMapper.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkStateMachine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkStateMachine.h
)

set(MODULE_LINK
    qlocky::Os
    qlocky::Persistence

    nlohmann_json::nlohmann_json
)

setup_module()
