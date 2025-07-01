pragma Singleton
import QtQuick 2.15

import "themes"

QtObject {
    enum ThemeMode { Light, Dark }

    property QtObject lightTheme: LightTheme {}
    property QtObject darkTheme: DarkTheme {}

    property int currentTheme: ThemeManager.ThemeMode.Dark
    readonly property QtObject theme: currentTheme === ThemeManager.ThemeMode.Light ? lightTheme : darkTheme

    function toggleTheme() {
        currentTheme = (currentTheme === ThemeManager.ThemeMode.Light) ? ThemeManager.ThemeMode.Dark : ThemeManager.ThemeMode.Light
    }

    function setTheme(mode) {
        if (mode === ThemeManager.ThemeMode.Light || mode === ThemeManager.ThemeMode.Dark) {
            currentTheme = mode
        }
    }
}
