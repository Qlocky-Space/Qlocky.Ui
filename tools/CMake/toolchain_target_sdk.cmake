# we simply load to toolchain file provided by the sdk. The sdk is installed in the default sdk installation
# directory on the WSL (Windows Subsystem for Linux)
include(/opt/poky/5.0/sysroots/x86_64-pokysdk-linux/usr/share/cmake/OEToolchainConfig.cmake)

# available configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug")