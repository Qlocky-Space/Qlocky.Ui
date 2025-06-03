cmake_minimum_required(VERSION 3.27)

set(TARGET_NAME QlockyApp)
project(${TARGET_NAME} LANGUAGES CXX)

set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/tools/CMake
    ${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

set(QLOCKY_LIBS_PATH "${CMAKE_CURRENT_LIST_DIR}/libs")
set(QLOCKY_SRC_PATH "${CMAKE_CURRENT_LIST_DIR}/src")

###########################################
# Application Options
###########################################
# Example option(QLOCKY_BUILD_APPSHELL_MODULE "Build appshell module" ON)

###########################################
# Setup compiler and build environment
###########################################
include(Version)
include(GetPlatformInfo)
include(SetupConfigure)
# TODO Enable CCache

###########################################
# Setup external dependencies
###########################################
include(SetupQt6)
include(SetupBoostDi)
include(DeclareModuleSetup)

###########################################
# Add source tree
###########################################
add_subdirectory(src)

if (OS_IS_LINUX)
    enable_testing()
    add_subdirectory(tests)
endif()