declare_module(Ui)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/UiEngineIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/CommandIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlCommandBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlRegistryUtil.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlCommandBase.cpp


    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.cpp
)

setup_module()
