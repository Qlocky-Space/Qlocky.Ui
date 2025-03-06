if (PLATFORM_DETECTED)
    return()
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OS_IS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Qlocky")
    set(OS_IS_QLOCKY 1)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(PLATFORM_DETECTED 1)
