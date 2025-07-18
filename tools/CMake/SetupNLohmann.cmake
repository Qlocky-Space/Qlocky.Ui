###########################################
# Third part dependencies
###########################################

include(FetchContent)
FetchContent_Declare(
  json
  URL      https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_GetProperties(json)

if(NOT json_POPULATED)
    FetchContent_MakeAvailable(json)
endif()

# Setup all used components
set(_components
  nlohmann_json::nlohmann_json
)

foreach(_component ${_components})
    list(APPEND EXTERN_LIBRARIES ${_component})
endforeach()
