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

    # just reset all settings
    unset(MODULE_INCLUDE)
    unset(MODULE_DEF)
    unset(MODULE_SRC)
    unset(MODULE_LINK)
    unset(MODULE_QRC)
    unset(MODULE_QML_IMPORT)
    unset(MODULE_INCLUDE_API)
endmacro()

macro(add_qml_import_path input_var)
    if (NOT ${input_var} STREQUAL "")
        set(QML_IMPORT_PATH "$CACHE{QML_IMPORT_PATH}")
        list(APPEND QML_IMPORT_PATH ${input_var})
        list(REMOVE_DUPLICATES QML_IMPORT_PATH)
        set(QML_IMPORT_PATH "${QML_IMPORT_PATH}" CACHE STRING
            "QtCreator extra import paths for QML modules" FORCE)
    endif()
endmacro()

macro(setup_module)
    message(STATUS "Configuring ${MODULE} <${MODULE_ALIAS}>")

    if (MODULE_QML_SRC)
        qt_add_library(${MODULE} STATIC)
        qt6_add_qml_module(${MODULE}
            URI ${MODULE}
            RESOURCE_PREFIX  "/qt/qml"
            QML_FILES ${MODULE_QML_SRC}
        )
        add_qml_import_path(${CMAKE_CURRENT_LIST_DIR}/qml)
    else()
        add_library(${MODULE})
    endif()

    if (MODULE_ALIAS)
        add_library(${MODULE_ALIAS} ALIAS ${MODULE})
    endif()

    target_sources(${MODULE} PRIVATE ${MODULE_SRC})

    target_include_directories(${MODULE} PUBLIC
        # Default include folder for all modules
        ${QLOCKY_SRC_PATH}/Global

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
    )

    string(TOUPPER ${MODULE} MODULE_UPPERCASE)
    target_compile_definitions(${MODULE} PUBLIC
        ${MODULE_DEF}
        # ${MODULE_UPPERCASE}_QML_IMPORT="${MODULE_QML_IMPORT}"
    )

    list(APPEND MODULE_LINK ${EXTERN_LIBRARIES})

    target_link_libraries(${MODULE} PRIVATE ${MODULE_LINK})
endmacro()