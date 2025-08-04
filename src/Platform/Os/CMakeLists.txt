declare_module(Os)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/TimeProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkDriverIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/DeviceInfoProviderIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/DeviceInfoProvider.h
)

list(APPEND _links
    ng-log::ng-log
)

if (OS_IS_QLOCKY)
    list(APPEND MODULE_SRC
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantDBusDriver.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantDBusDriver.h
    )
else()
    list(APPEND MODULE_SRC
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/NetworkDriverStub.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/NetworkDriverStub.h
    )
endif()

set(MODULE_LINK ${_links})

setup_module()
