string(TIMESTAMP TODAY "%Y%m%d")

set(QLOCKY_APP_REVISION "${QLOCKY_APP_VERSION}-${TODAY}")
set(QLOCKY_APP_BUILD_NUMBER ${CMAKE_BUILD_NUMBER})
set(QLOCKY_APP_NAME "Qlocky Device")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###########################################
# Setup paths
###########################################
set(QLOCKY_INSTALL_NAME  "qlocky-${QLOCKY_APP_VERSION}")
set(QLOCKY_SHARE_NAME    "share")
set(QLOCKY_SHARE_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/${QLOCKY_SHARE_NAME}/${QLOCKY_INSTALL_NAME}")

###########################################
# Global definitions
###########################################
configure_file(${CMAKE_CURRENT_LIST_DIR}/QlockyConfig.h.in QlockyConfig.h )

###########################################
# Compiler commands
###########################################
function(def_opt name val)
    if (val)
        add_compile_definitions(${name})
    endif()
endfunction()

def_opt(OS_IS_LINUX ${OS_IS_LINUX})
def_opt(OS_IS_QLOCKY ${OS_IS_QLOCKY})
