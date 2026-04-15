set(CMAKE_TARGET_SDK Qlocky)

include($ENV{OECORE_NATIVE_SYSROOT}/usr/share/cmake/OEToolchainConfig.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")

# Read the contents of the file
file(STRINGS /workspaces/.env ENV_FILE)
foreach(VAR ${ENV_FILE})
    string(REGEX MATCH "^[^=]*" KEY ${VAR})
    string(REGEX REPLACE "^[^=]*=" "" VALUE ${VAR})
    set(ENV{${KEY}} ${VALUE})
endforeach()

# ensure any change on env file will trigger reconfiguration
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS /workspaces/.env)

# Custom VSCode launch
set(VSCODE_LAUNCH_COMMANDS [[
    "linux": {
        "preLaunchTask": "Qlocky: Prepare Target",
        "envFile": "/workspaces/.env",
        "miDebuggerServerAddress": "$ENV{REMOTE_HOST}:2000",
        "MIMode": "gdb",
        "setupCommands": [
                {
                    "text": "-enable-pretty-printing"
                }
        ],
        "miDebuggerPath": "$ENV{OECORE_NATIVE_SYSROOT}/usr/bin/aarch64-poky-linux/aarch64-poky-linux-gdb"
    }
]])
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "/workspaces/tools/CMake/generate_vscode_files.cmake")
