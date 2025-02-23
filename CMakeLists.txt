cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME QlockyApp)

set(CMAKE_PREFIX_PATH "$ENV{OECORE_NATIVE_SYSROOT}/usr/lib")
set(QT_HOST_PATH "$ENV{OECORE_NATIVE_SYSROOT}/usr/lib")
set(QT_HOST_PATH_CMAKE_DIR "$ENV{OECORE_NATIVE_SYSROOT}/usr/lib/cmake")



set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})

project(${TARGET_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)
qt_standard_project_setup()

add_executable(${TARGET_NAME}
    src/main.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick)

# Configure Qt
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

qt_add_qml_module(${TARGET_NAME}
    URI QlockyModule
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        src/mainwindow.qml
)

include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


install(TARGETS ${TARGET_NAME})
