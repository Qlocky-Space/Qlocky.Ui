###########################################
# Qlocky image dependency setup
###########################################

include(FetchContent)
FetchContent_Declare(
  ng-log
  URL https://github.com/ng-log/ng-log/archive/refs/tags/v0.8.1.tar.gz
)
FetchContent_GetProperties(ng-log)

# Disable building ng-log's tests to avoid build errors with non-standard code
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(WITH_GFLAGS OFF CACHE BOOL "" FORCE)
set(WITH_GTEST OFF CACHE BOOL "" FORCE)
set(WITH_SYMBOLIZE OFF CACHE BOOL "" FORCE)

if(NOT ng-log_POPULATED)
    FetchContent_MakeAvailable(ng-log)

    # Remove -Wpedantic for ng-log targets if they exist
    foreach(_target ng-log ng-log_internal stacktrace_unittest)
      if(TARGET ${_target})
          target_compile_options(${_target} PRIVATE -Wno-pedantic)
      endif()
    endforeach()
endif()

# Setup all used components
set(_components
  ng-log::ng-log
)

foreach(_component ${_components})
    list(APPEND EXTERN_LIBRARIES ${_component})
endforeach()
