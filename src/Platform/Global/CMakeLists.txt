declare_module(Global)


set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/ModuleBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/ApplicationIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/api/Mediator.h
    ${CMAKE_CURRENT_LIST_DIR}/api/EventIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/util/StringUtil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/util/StringUtil.h
)

setup_module()