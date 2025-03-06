string(TIMESTAMP TODAY "%Y%m%d")

set(QLOCKY_APP_REVISION "${QLOCKY_APP_VERSION}-${TODAY}")
set(QLOCKY_APP_BUILD_NUMBER ${CMAKE_BUILD_NUMBER})


###########################################
# Global definitions
###########################################
configure_file(${CMAKE_CURRENT_LIST_DIR}/QlockyConfig.h.in QlockyConfig.h )
