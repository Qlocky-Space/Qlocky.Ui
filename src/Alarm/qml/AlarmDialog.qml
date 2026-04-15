import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmDialogViewModel
    property var alarm: viewModel.item
    property bool subPageActive: false

    property string alarmId

    implicitWidth: 1000
    implicitHeight: contentLoader.implicitHeight + 180

    acceptText: subPageActive ? qsTr("Choose") : qsTr("Save")
    cancelText: subPageActive ? qsTr("Return") : qsTr("Cancel")

    onOpened: {
        viewModel.loadAlarm(alarmId);
    }

    onCanceled: {
        if (subPageActive) {
            contentLoader.sourceComponent = mainComponent;
        } else {
            close();
        }
    }

    onAccepted: {
        if (subPageActive) {
            if (contentLoader.item) {
                contentLoader.item.confirmSelection();
            }
        } else {
            viewModel.save();
            close();
        }
    }

    Connections {
        target: contentLoader.item

        function onDone() {
            root.subPageActive = false;
            contentLoader.sourceComponent = mainComponent;
        }
    }

    Connections {
        target: contentLoader.sourceComponent === mainComponent ? contentLoader.item : null

        function onShowComponent(component) {
            root.subPageActive = (component !== mainComponent);
            contentLoader.sourceComponent = component;
        }
    }

    Component {
        id: repeatedComponent
        AlarmDialogRepeated {
            alarm: root.alarm
        }
    }

    Component {
        id: musicComponent
        AlarmDialogMusicSource {
            alarm: root.alarm
        }
    }

    Component {
        id: mainComponent

        AlarmDialogMain {
            anchors.fill: parent
            alarm: root.alarm
        }
    }

    Loader {
        id: contentLoader
        anchors.fill: parent

        sourceComponent: mainComponent
        active: true
    }
}
