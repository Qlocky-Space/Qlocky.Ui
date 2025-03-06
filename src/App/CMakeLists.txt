###########################################
# Platform specific
###########################################
include(GetPlatformInfo)


###########################################
# Dependency library declaration
###########################################
set(LINK_LIB
    qlocky::Global
)
foreach(_module ${QLOCKY_MODULES})
    list(APPEND LINK_LIB qlocky::${_module})
endforeach()

###########################################
# Resources
###########################################
# no resources required

###########################################
# Executable declaration
###########################################
add_executable(QlockyApp
    ${APP_RCC_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/Main.cpp

    ${CMAKE_CURRENT_LIST_DIR}/internal/QlockyApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/QlockyApp.h
)

###########################################
# Setting target properties
###########################################
target_include_directories(QlockyApp PRIVATE
    ${CMAKE_BINARY_DIR}
)

###########################################
# Link
###########################################
target_link_libraries(QlockyApp ${EXTERN_LIBRARIES} ${LINK_LIB})

###########################################
# INSTALL
###########################################
install(TARGETS QlockyApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

