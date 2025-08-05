declare_module(Device)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceInfoProviderIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.h
)

setup_module()
