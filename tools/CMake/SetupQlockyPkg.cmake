###########################################
# Qlocky image dependency setup
###########################################

if (OS_IS_QLOCKY)
  find_package(sdbus-c++ REQUIRED)

  # Setup all used components
  set(_components
    SDBusCpp::sdbus-c++
  )

  foreach(_component ${_components})
  list(APPEND EXTERN_LIBRARIES ${_component})
  endforeach()
endif()
