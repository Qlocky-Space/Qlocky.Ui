cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME QlockyApp)
project(${TARGET_NAME} VERSION 0.1 LANGUAGES CXX)

# Project Configurations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# The main application
add_subdirectory(src)

# The test application
enable_testing()
add_subdirectory(tests)