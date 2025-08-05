declare_module(Ui)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/UiModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/UiEngineIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Navigation/InteractiveNavigatorIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Navigation/InteractiveUriRegistryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Navigation/NavigateToEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Navigation/NavigateToCommand.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/CommandIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/QmlCommandBase.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/QmlCommandBase.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/CommandRegistryUtil.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Command/CommandArgs.h
    ${CMAKE_CURRENT_LIST_DIR}/api/QmlRegistryUtil.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveNavigator.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveNavigator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveUriRegistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/InteractiveUriRegistry.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/CommandDispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/CommandDispatcher.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/CommandExecutor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/CommandExecutor.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/QRCodeGen/qrcodegen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/QRCodeGen/qrcodegen.hpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrGenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrQuickImageProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrQuickImageProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrImage.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/QrImage.cpp
)

set(MODULE_QML_SRC
    qml/internal/AutoScroller.qml
    qml/QButton.qml
    qml/QStatusButton.qml
    qml/QIcon.qml
    qml/QInteractiveProvider.qml
    qml/QDialog.qml
    qml/QLabel.qml
    qml/QRoundedRectangle.qml
    qml/QToggleButton.qml
    qml/QTimePicker.qml
    qml/QKeyboard.qml
    qml/QConfirmationSlider.qml
    qml/QDialogProvider.qml
    qml/FontStyle.qml
    qml/ThemeManager.qml
    qml/themes/DarkTheme.qml
    qml/themes/LightTheme.qml
)

set(MODULE_QML_RESOURCES
    resources/SF-Pro-Display-Regular.otf
    resources/Font-Awesome-6-Solid-900.otf
    resources/custom-fa-solid-900.ttf
)

set(MODULE_SHADERS
    resources/shaders/gaussianblur.frag
)

# Make the available as a singleton
set_source_files_properties(qml/ThemeManager.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
set_source_files_properties(qml/FontStyle.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

setup_module()
