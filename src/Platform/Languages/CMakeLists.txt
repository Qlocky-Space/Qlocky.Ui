declare_module(Languages)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/LanguageServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/LanguageService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/LanguageService.h
)

set(MODULE_LINK
    qlocky::Ui
)

setup_module()
