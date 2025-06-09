file(GLOB TS_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/*.ts)

qt_add_translations(QlockyApp
    TS_FILES ${TS_FILES}
    INCLUDE_DIRECTORIES ${QLOCKY_SRC_PATH}
    NO_GLOBAL_TARGET
    QM_FILES_OUTPUT_VARIABLE QM_FILES
)

message(STATUS "Translations installed to: " ${QLOCKY_SHARE_INSTALL_PATH}/locale)
install(DIRECTORY
    ${QLOCKY_SHARE_PATH}/i18n/
    DESTINATION ${QLOCKY_SHARE_INSTALL_PATH}/locale
    FILES_MATCHING
    REGEX "qt_.*\\.qm"
    REGEX "qt_help_.*\\.qm" EXCLUDE
    REGEX "qtbase_.*\\.qm"
    REGEX "qt*_en\\.qm" EXCLUDE)