import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmDialogViewModel
    property var alarm: viewModel.item

    property string alarmId

    implicitWidth: 800
    implicitHeight: contentLoader.implicitHeight + 180

    onOpened: {
        viewModel.loadAlarm(alarmId);
    }

    onCanceled: {
        close();
    }

    onAccepted: {
        viewModel.save();
        close();
    }

    Connections {
        target: contentLoader.item

        function onDone() {
            contentLoader.sourceComponent = mainComponent;
        }
    }

    Component {
        id: repeatedComponent
        AlarmDialogRepeated {
            alarm: root.alarm
        }
    }

    Component {
        id: mainComponent

        AlarmDialogMain {
            anchors.fill: parent
            alarm: root.alarm

            onShowComponent: function(component) {
                contentLoader.sourceComponent = component;
            }
        }
    }

    Loader {
        id: contentLoader
        anchors.fill: parent

        sourceComponent: mainComponent
        active: true
    }
}
