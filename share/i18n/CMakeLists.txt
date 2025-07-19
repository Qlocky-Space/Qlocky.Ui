file(GLOB TS_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.ts)

# TODO environment configuration issue, where LinguistTools is not found
# on Linux, but it is available in the Qt installation.
# This is a workaround to ensure that the build does not fail on Target.
if (OS_IS_LINUX)
    qt_add_translations(QlockyApp
        TS_FILES ${TS_FILES}
        INCLUDE_DIRECTORIES ${QLOCKY_SRC_PATH}
        NO_GLOBAL_TARGET
        QM_FILES_OUTPUT_VARIABLE QM_FILES
    )
endif()
