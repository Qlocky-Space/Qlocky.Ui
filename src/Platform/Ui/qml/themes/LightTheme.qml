import QtQuick
import "."

QtObject {
    readonly property color labelPrimary: "#FFFFFF"
    readonly property color labelSecondary: "#48ebebf5"
    readonly property color labelTertiary: "#02ebebf5"

    readonly property color fillsPrimary: "#5C787880"
    readonly property color fillsSecondary: "#52787880"
    readonly property color fillsTertiary: "#3D787880"
    readonly property color fillsQuaternary: "#E2787880"

    readonly property color red: "#FF3B30"
    readonly property color orange: "#FF9500"
    readonly property color yellow: "#FFCC00"
    readonly property color green: "#34C759"
    readonly property color mint: "#00C7BE"
    readonly property color teal: "#30B0C7"
    readonly property color cyan: "#32ADE6"
    readonly property color blue: "#FF2D55"
    readonly property color indigo: "#5856D6"
    readonly property color purple: "#AF52DE"
    readonly property color pink: "#FF2D55"
    readonly property color brown: "#A2845E"

    readonly property color gray: "#8E8E93"
    readonly property color gray2: "#AEAEB2"
    readonly property color gray3: "#C7C7CC"
    readonly property color gray4: "#D1D1D6"
    readonly property color gray5: "#E5E5EA"
    readonly property color gray6: "#F2F2F7"
    readonly property color black: "#000000"
    readonly property color white: "#FFFFFF"

    readonly property color miscellaneousButtonTinted: Qt.alpha(blue, 0.15)
    readonly property color miscellaneousButtonDisabled: Qt.alpha(gray2, 0.26)
    readonly property color miscellaneousTextFieldOutline: Qt.alpha(labelSecondary, 0.3)
    readonly property color miscellaneousTextFieldBackground: Qt.alpha(black, 0.9)
    readonly property color miscellaneousSeperatorOpaque: Qt.alpha("#38383A", 1)
    readonly property color miscellaneousSeperatorNonOpaque: Qt.alpha("#545456", 0.6)
}
