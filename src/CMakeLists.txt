# A list of all used modules
set(QLOCKY_MODULES
    AppShell
    Alarm
    Weather
    Radio
)

add_subdirectory(Platform)
add_subdirectory(App)

foreach(_module ${QLOCKY_MODULES})
    add_subdirectory(${_module})
endforeach()