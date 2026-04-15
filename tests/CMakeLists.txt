cmake_minimum_required(VERSION 3.27)

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
    TestTimeConverter.cpp
    TestPskEncryption.cpp
    TestUuid.cpp
    TestSubjectThreadSafety.cpp
    TestNetworkDriverStubConcurrency.cpp
)

target_include_directories(${TARGET_NAME}Test PRIVATE
    .
    ../src/Alarm
    ../src/Platform/Global/api
    ../src/Platform/Os/api
    ../src/Platform/Os/internal/mock
    ../src/Platform/Network
    ../src/Platform/Device
)

target_link_libraries(${TARGET_NAME}Test PRIVATE
    GTest::gmock_main
    qlocky::Global
    qlocky::Os
    qlocky::Alarm
    qlocky::Device
    qlocky::Network

    nlohmann_json::nlohmann_json
    crypto
)

add_test(${TARGET_NAME}Test ${TARGET_NAME}Test --gtest_output=json:report.json)