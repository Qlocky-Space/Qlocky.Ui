set(MODULE VirtualKeyboardResources)

qt_add_library(${MODULE} STATIC)
qt_add_qml_module(${MODULE}
    # NOTE: It's very important that URI matches so virtual keyboard
    # can find the styles and layouts.
    URI QtQuick.VirtualKeyboard.Styles.qlocky
    PLUGIN_TARGET ${MODULE}Plugin
    VERSION 1.0
    QML_FILES
        style.qml

    RESOURCE_PREFIX /qt/qml
)

qt6_add_resources(${MODULE} "${MODULE}-resources"
    PREFIX ${MODULE}
    FILES
        images/backspace-fff.svg
        images/check-fff.svg
        images/enter-fff.svg
        images/globe-fff.svg
        images/handwriting-fff.svg
        images/hidekeyboard-fff.svg
        images/search-fff.svg
        images/selectionhandle-bottom.svg
        images/settings-fff.svg
        images/shift-80c342.svg
        images/shift-c5d6b6.svg
        images/shift-fff.svg
        images/textmode-fff.svg

        layouts/fallback/digits.qml
        layouts/fallback/numbers.qml
        layouts/fallback/symbols.qml
        layouts/fallback/dialpad.qml
        layouts/fallback/handwriting.qml
        layouts/fallback/main.qml
        layouts/en_US/dialpad.fallback
        layouts/en_US/handwriting.fallback
        layouts/en_US/numbers.fallback
        layouts/en_US/symbols.fallback
        layouts/en_US/digits.fallback
        layouts/en_US/main.fallback
        layouts/de_CH/dialpad.fallback
        layouts/de_CH/handwriting.fallback
        layouts/de_CH/numbers.fallback
        layouts/de_CH/symbols.fallback
        layouts/de_CH/digits.fallback
        layouts/de_CH/main.qml
)
