###########################################
# Qlocky image dependency setup
###########################################

find_package(OpenSSL REQUIRED)
set(_components
  ssl
  crypto
)

if (OS_IS_QLOCKY)
  find_package(sdbus-c++ REQUIRED)

  # Setup all used components
  list(APPEND _components
    SDBusCpp::sdbus-c++
  )
endif()


foreach(_component ${_components})
  list(APPEND EXTERN_LIBRARIES ${_component})
endforeach()
