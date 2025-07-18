declare_module(Persistence)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesContextIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesServiceIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/PreferencesService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/PreferencesService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/PreferencesContext.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/PreferencesContext.cpp
)

set(MODULE_LINK
    rocksdb
)

setup_module()
