declare_module(Os)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/TimeProviderIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.h
)

setup_module()
