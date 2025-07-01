// LightTheme.qml
import QtQuick
import "."

QtObject {
    readonly property color labelPrimary: "#000000"
    readonly property color labelSecondary: "#993C3C43"
    readonly property color labelTertiary: "#4D3C3C43"

    readonly property color fillsPrimary: "#33787880"
    readonly property color fillsSecondary: "#29787880"
    readonly property color fillsTertiary: "#1F787880"
    readonly property color fillsQuaternary: "#14787880"

    readonly property color backgroundPrimary: "#FFFFFFFF"
    readonly property color backgroundSecondary: "#FFF2F2F7"
    readonly property color backgroundTertiary: "#FFFFFFFF"

    readonly property color red: "#FF3B30"
    readonly property color orange: "#FF9500"
    readonly property color yellow: "#FFCC00"
    readonly property color green: "#34C759"
    readonly property color mint: "#00C7BE"
    readonly property color teal: "#30B0C7"
    readonly property color cyan: "#32ADE6"
    readonly property color blue: "#0A84FF"
    readonly property color indigo: "#5856D6"
    readonly property color purple: "#AF52DE"
    readonly property color pink: "#FF2D55"
    readonly property color brown: "#A2845E"

    readonly property color gray: "#6E6E73"
    readonly property color gray2: "#8E8E93"
    readonly property color gray3: "#AEAEB2"
    readonly property color gray4: "#C7C7CC"
    readonly property color gray5: "#D1D1D6"
    readonly property color gray6: "#E5E5EA"
    readonly property color black: "#000000"
    readonly property color white: "#FFFFFF"

    readonly property color miscellaneousButtonTinted: Qt.alpha(blue, 0.15)
    readonly property color miscellaneousButtonDisabled: Qt.alpha(gray2, 0.3)
    readonly property color miscellaneousTextFieldOutline: Qt.alpha(labelSecondary, 0.4)
    readonly property color miscellaneousTextFieldBackground: "#F2F2F7" // light gray background
    readonly property color miscellaneousSeperatorOpaque: "#C6C6C8"
    readonly property color miscellaneousSeperatorNonOpaque: Qt.alpha("#C6C6C8", 0.6)
}