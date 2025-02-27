cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME QlockyApp)
project(${TARGET_NAME} VERSION 0.1 LANGUAGES CXX)

# Project Configurations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

# The main application
add_subdirectory(src)

# The test application
# Only enable test when building for host
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "AMD64")
    message(STATUS "UnitTests enabled for AMD64 Target")

    enable_testing()
    add_subdirectory(tests)
endif()