###########################################
# Third part dependencies
###########################################

include(FetchContent)
FetchContent_Declare(
  boost_di
  URL      https://github.com/boost-ext/di/archive/refs/tags/v1.3.2.zip
)
FetchContent_GetProperties(boost_di)

if(NOT boost_di_POPULATED)
    FetchContent_MakeAvailable(boost_di)
endif()

# Create interface library for linking
add_library(boost-di INTERFACE)
target_include_directories(boost-di INTERFACE ${boost_di_SOURCE_DIR}/include)
target_include_directories(boost-di INTERFACE ${boost_di_SOURCE_DIR}/extension/include)

# Setup all used boost compoents
set(_components
  boost-di
)

foreach(_component ${_components})
    list(APPEND EXTERN_LIBRARIES ${_component})
endforeach()
