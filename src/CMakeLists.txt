# A list of all used platform modules
set(QLOCKY_MODULES_PLATFORM
    Global
    Os
    Preferences
    Languages
    Ui
    Widget
)

# A list of all used modules
set(QLOCKY_MODULES
    AppShell
    Alarm
    Radio
)

foreach(_module ${QLOCKY_MODULES_PLATFORM})
    add_subdirectory(Platform/${_module})
endforeach()

foreach(_module ${QLOCKY_MODULES})
    add_subdirectory(${_module})
endforeach()

add_subdirectory(App)