cmake_minimum_required(VERSION 3.16)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_MakeAvailable(googletest)
endif()

# Generated with VSCode Task
add_executable(${TARGET_NAME}Test
    #
    demo.cpp
)

target_include_directories(${TARGET_NAME}Test PRIVATE
    .
)

target_link_libraries(${TARGET_NAME}Test PRIVATE
    GTest::gmock_main
)

add_test(${TARGET_NAME}Test ${TARGET_NAME}Test --gtest_output=json:report.json)