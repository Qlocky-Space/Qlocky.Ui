declare_module(Persistence)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/PreferencesModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/KeyValueDatabaseIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/PersistenceServiceIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/PersistenceService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/PersistenceService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/KeyValueDatabase.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/KeyValueDatabase.cpp
)

set(MODULE_LINK
    rocksdb
)

setup_module()
