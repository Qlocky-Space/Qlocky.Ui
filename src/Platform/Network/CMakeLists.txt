declare_module(Network)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/NetworkStatusEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkServiceIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/NetworkService.h
)

set(MODULE_LINK
    qlocky::Os
    qlocky::Persistence
)

setup_module()
