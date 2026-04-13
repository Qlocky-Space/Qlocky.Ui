declare_module(Os)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AudioOutputErrorCode.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AudioMixerIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AudioMixerListenerIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AudioOutputIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AudioOutputListenerIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/AudioOutputVolumeEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/OsModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/TimeProviderIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NetworkDriverIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/AsyncTaskExecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AsyncTaskExecutor.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/TimeProvider.h
)

list(APPEND _links
    ng-log::ng-log
)

if (OS_IS_QLOCKY)
    list(APPEND MODULE_SRC
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/AudioOutputMixer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/AudioOutputMixer.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/AudioOutputProcessDriver.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/AudioOutputProcessDriver.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantDBusDriver.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/qlocky/WpaSupplicantDBusDriver.h
    )
else()
    list(APPEND MODULE_SRC
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/AudioMixerStub.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/AudioMixerStub.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/AudioOutputStub.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/AudioOutputStub.h
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/NetworkDriverStub.cpp
        ${CMAKE_CURRENT_LIST_DIR}/internal/mock/NetworkDriverStub.h
    )
    list(APPEND _links
        Qt6::Multimedia
    )
endif()

if (OS_IS_QLOCKY)
    list(APPEND _links
        asound
    )
endif()

set(MODULE_LINK ${_links})

setup_module()
