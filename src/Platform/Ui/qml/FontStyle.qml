pragma Singleton

import QtQuick

QtObject {
    readonly property FontLoader sfProFont: FontLoader { source: "/Ui/resources/SF-Pro-Display-Regular.otf" }
    readonly property FontLoader fontAwesomeFont: FontLoader { source: "/Ui/resources/fa-solid-900.ttf" }

    readonly property font fontAwesome: Qt.font({ family: fontAwesomeFont.name, pointSize: 42 })

    readonly property font h1: Qt.font({ family: sfProFont.name, pointSize: 52, bold: true })
    readonly property font h2: Qt.font({ family: sfProFont.name, pointSize: 48, bold: true })

    readonly property font body:  Qt.font({ family: sfProFont.name, pointSize: 42 })
    readonly property font caption: Qt.font({ family: sfProFont.name, pointSize: 32 })
    readonly property font subCaption: Qt.font({ family: sfProFont.name, pointSize: 28 })
}