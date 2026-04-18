

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(QLOCKY_ENABLE_QT_VIRTUALKEYBOARD "Enable Qt Virtual Keyboard integration" ON)

set(_components
    Core
    Gui
    Multimedia
    Network
    Qml
    Quick
    ShaderTools
)

if (QLOCKY_ENABLE_QT_VIRTUALKEYBOARD)
    list(APPEND _components
        VirtualKeyboard
    )
endif()

# TODO environment configuration issue, where LinguistTools is not found
# on Linux, but it is available in the Qt installation.
# This is a workaround to ensure that the build does not fail on Target.
if (OS_IS_LINUX)
    list(APPEND _components
        LinguistTools
    )
endif()

set(QT_QML_GENERATE_QMLLS_INI ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY} CACHE PATH "Extra QML import paths to make Qt Creator happy")

foreach(_component ${_components})
    find_package(Qt6${_component} REQUIRED)
    list(APPEND EXTERN_LIBRARIES ${Qt6${_component}_LIBRARIES})
    list(APPEND QT_INCLUDES ${Qt6${_component}_INCLUDE_DIRS})
    add_definitions(${Qt6${_component}_DEFINITIONS})
endforeach()

# Suppress warning about missing QML import paths
qt_policy(SET QTP0004 NEW)

include_directories(${QT_INCLUDES})

qt6_standard_project_setup()
