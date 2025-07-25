import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    property color color: ThemeManager.theme.blue
    property color foreground: ThemeManager.theme.labelPrimary

    property string sliderImage
    property string image
    property string imageInactive: image

    property bool status
    property real value: 0.0

    implicitHeight: 90
    implicitWidth: 700


    signal valueUpdated(real newValue)
    signal clicked()

    RowLayout {
        spacing: 10
        anchors.fill: parent

        QStatusBarSlider {
            id: slider
            color: root.color
            foreground: root.foreground
            image: root.sliderImage
            value: root.value

            Layout.fillWidth: true

            onValueUpdated: function(newValue) {
                root.valueUpdated(newValue);
            }
        }

        QStatusButton {
            image: root.image
            imageInactive: root.imageInactive

            onClicked: root.clicked()
            status: root.status
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
        }
    }
}
