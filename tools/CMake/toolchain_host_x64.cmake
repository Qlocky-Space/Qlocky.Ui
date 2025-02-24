# add standard compiler search path
LIST(PREPEND CMAKE_PROGRAM_PATH usr/bin)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

set(CMAKE_C_COMPILER gcc CACHE PATH "C compiler")
set(CMAKE_CXX_COMPILER g++ CACHE PATH "C++ compiler")

# c++17 + -Wpedantic ensure that "linux" is not converted to "1" by the gcc preprocessor
set(CMAKE_CXX_FLAGS "-std=c++17 -Wpedantic -Werror -DQT_QML_DEBUG")
set(CMAKE_C_FLAGS "-Wpedantic -Werror")

set(QT_INST_DIR "/opt/qt/6.8.1/gcc_64")
set(CMAKE_PREFIX_PATH ${QT_INST_DIR})
set(QT_HOST_PATH ${QT_INST_DIR})
set(QT_QMAKE_EXECUTABLE ${QT_INST_DIR}/bin/qmake)
set(CMAKE_INSTALL_RPATH "${QT_INST_DIR}/lib")

# Custopm VSCode launch
set(VSCODE_LAUNCH_COMMANDS [[
    "linux": {
        "preLaunchTask": "CMake: Build",
        "MIMode": "gdb",
        "miDebuggerPath": "gdb"
    }
]])
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "/workspaces/tools/CMake/generate_vscode_files.cmake")
