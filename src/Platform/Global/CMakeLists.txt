declare_module(Global)


set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/ModuleBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/ApplicationIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Task.h

    ${CMAKE_CURRENT_LIST_DIR}/api/Mediator.h
    ${CMAKE_CURRENT_LIST_DIR}/api/EventIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Stream.h
    ${CMAKE_CURRENT_LIST_DIR}/api/TaskExecutorIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/util/StringUtil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/StringUtil.h

    ${CMAKE_CURRENT_LIST_DIR}/types/Uri.cpp
    ${CMAKE_CURRENT_LIST_DIR}/types/Uri.h
    ${CMAKE_CURRENT_LIST_DIR}/types/UriQuery.cpp
    ${CMAKE_CURRENT_LIST_DIR}/types/UriQuery.h
    ${CMAKE_CURRENT_LIST_DIR}/types/Uuid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/types/Uuid.h
)

setup_module()