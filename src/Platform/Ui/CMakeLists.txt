declare_module(Ui)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/UiEngineIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/CommandIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlCommandBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlRegistryUtil.h
    ${CMAKE_CURRENT_LIST_DIR}/api/NavigatorIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlCommandBase.cpp


    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/PageNavigator.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/PageNavigator.cpp
)

set(MODULE_QML_SRC
    qml/QButton.qml
    qml/QIcon.qml
    qml/FontStyle.qml
    qml/ThemeManager.qml
    qml/themes/DarkTheme.qml
    qml/themes/LightTheme.qml
)

set(MODULE_QML_RESOURCES
    resources/SF-Pro-Display-Regular.otf
    resources/Font-Awesome-6-Solid-900.otf
)

# Make the available as a singleton
set_source_files_properties(qml/ThemeManager.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
set_source_files_properties(qml/FontStyle.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

setup_module()
