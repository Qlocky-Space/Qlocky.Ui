declare_module(Languages)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/LanguageService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/LanguageService.h
)

setup_module()
