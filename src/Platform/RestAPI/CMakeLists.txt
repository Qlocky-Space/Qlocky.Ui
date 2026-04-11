declare_module(RestAPI)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/RestApiCode.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RestApi.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RestApiModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/RestApiModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/RestApiRequestOptions.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/JsonRestFulApi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/JsonRestFulApi.h
)

set(MODULE_LINK
    nlohmann_json::nlohmann_json
)

setup_module()