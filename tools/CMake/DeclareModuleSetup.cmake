## Declare
# declare_module(somename) - set module (target) name

## Setup
# set(MODULE somename)                        - set module (target) name
# set(MODULE_ALIAS somename)                  - set module (target) alias name
# set(MODULE_INCLUDE ...)                     - set include (by default see below include_directories)
# set(MODULE_DEF ...)                         - set definitions
# set(MODULE_SRC ...)                         - set sources and headers files
# set(MODULE_LINK ...)                        - set libraries for link
# set(MODULE_QRC somename.qrc)                - set resource (qrc) file
# set(MODULE_QML_IMPORT ...)                  - set Qml import for QtCreator (so that there is code highlighting, jump, etc.)

# After all the settings you need to do:
# setup_module()


macro(declare_module name)
    set(MODULE ${name})
    set(MODULE_ALIAS qlocky::${name})
    set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml)

    # just reset all settings
    unset(MODULE_INCLUDE)
    unset(MODULE_DEF)
    unset(MODULE_SRC)
    unset(MODULE_LINK)
    unset(MODULE_INCLUDE_API)
    unset(MODULE_QML_SRC)
    unset(MODULE_QML_RESOURCES)
endmacro()

macro(add_qml_import_path input_var)
    set(QML_IMPORT_PATH "$CACHE{QML_IMPORT_PATH}")
    list(APPEND QML_IMPORT_PATH ${input_var})
    list(REMOVE_DUPLICATES QML_IMPORT_PATH)
    set(QML_IMPORT_PATH "${QML_IMPORT_PATH}")
endmacro()

macro(setup_module)
    message(STATUS "Configuring ${MODULE} <${MODULE_ALIAS}>")

    if (MODULE_QML_SRC)
        qt_add_library(${MODULE} STATIC)
        qt_add_qml_module(${MODULE}
            URI ${MODULE}
            PLUGIN_TARGET ${MODULE}Plugin
            VERSION 1.0
            RESOURCE_PREFIX  "/qt/qml"
            IMPORTS ${MODULE_QML_IMPORTS}
            QML_FILES ${MODULE_QML_SRC}
            SOURCES ${MODULE_SRC}
        )
    else()
        add_library(${MODULE})
        target_sources(${MODULE} PRIVATE ${MODULE_SRC})
    endif()

    if (MODULE_QML_RESOURCES)
        qt6_add_resources(${MODULE} "${MODULE}-resources"
            PREFIX ${MODULE}
            FILES ${MODULE_QML_RESOURCES}
        )
    endif()

    if (MODULE_ALIAS)
        add_library(${MODULE_ALIAS} ALIAS ${MODULE})
    endif()


    target_include_directories(${MODULE} PUBLIC
        # Default include folder for all modules
        ${QLOCKY_SRC_PATH}/Platform
        ${QLOCKY_SRC_PATH}/Platform/Global

        # public API interface between modules
        ${CMAKE_CURRENT_LIST_DIR}/api
        ${CMAKE_CURRENT_BINARY_DIR}
        ${MODULE_INCLUDE_API}
    )

    target_include_directories(${MODULE} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_LIST_DIR}
        ${MODULE_INCLUDE}

        ${CMAKE_CURRENT_SOURCE_DIR}    # Include the current module source directory
        ${CMAKE_CURRENT_LIST_DIR}/view
    )

    string(TOUPPER ${MODULE} MODULE_UPPERCASE)
    target_compile_definitions(${MODULE} PUBLIC
        ${MODULE_DEF}
        ${MODULE_UPPERCASE}_QML_IMPORT="${MODULE_QML_IMPORT}"
    )

    if (NOT "${MODULE}" STREQUAL "Global")
        list(APPEND MODULE_LINK "Global")
    endif()

    list(APPEND MODULE_LINK ${EXTERN_LIBRARIES})

    target_link_libraries(${MODULE} PRIVATE ${MODULE_LINK})
endmacro()