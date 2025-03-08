if (PLATFORM_DETECTED)
    return()
endif()

set(OS_IS_LINUX OFF)
set(OS_IS_QLOCKY OFF)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OS_IS_LINUX ON)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Qlocky")
    set(OS_IS_QLOCKY ON)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

set(PLATFORM_DETECTED ON)
