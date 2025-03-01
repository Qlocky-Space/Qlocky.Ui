cmake_minimum_required(VERSION 3.16)

find_package(Qt6 COMPONENTS Core Gui Qml Quick REQUIRED)
qt_standard_project_setup()

# Generated with VSCode Task
add_executable(${TARGET_NAME}
    #
    main.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE
    .
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
        mainwindow.qml
)

# Installation, also used for Yocto build
include(GNUInstallDirs)
install(TARGETS ${TARGET_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


install(TARGETS ${TARGET_NAME})
