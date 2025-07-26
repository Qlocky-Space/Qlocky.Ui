###########################################
# Qlocky image dependency setup
###########################################

if (OS_IS_QLOCKY)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(LIBNL REQUIRED IMPORTED_TARGET
  libnl-3.0
  libnl-genl-3.0
  )

  # Setup all used components
  set(_components
  PkgConfig::LIBNL
  )

  foreach(_component ${_components})
  list(APPEND EXTERN_LIBRARIES ${_component})
  endforeach()
endif()
