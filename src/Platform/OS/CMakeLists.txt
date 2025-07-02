declare_module(Os)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/TimeServiceIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeService.h
)

setup_module()
