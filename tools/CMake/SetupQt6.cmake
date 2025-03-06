

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(_components
    Core
    Gui
    Qml
    Quick
)

set(QT_QML_GENERATE_QMLLS_INI ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
# set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY} CACHE STRING "Import paths for Qt Creator's code model" FORCE)

foreach(_component ${_components})
    find_package(Qt6${_component} REQUIRED)
    list(APPEND EXTERN_LIBRARIES ${Qt6${_component}_LIBRARIES})
    list(APPEND QT_INCLUDES ${Qt6${_component}_INCLUDE_DIRS})
    add_definitions(${Qt6${_component}_DEFINITIONS})
endforeach()

include_directories(${QT_INCLUDES})

qt6_standard_project_setup()
