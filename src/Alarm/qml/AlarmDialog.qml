import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmDialogViewModel

    property string text: "Label"
    property date dueTime: new Date(Date.now())
    property bool isActive: true

    onCanceled: {
        close();
    }

    onAccepted: {
        viewModel.save();
        close();
    }

    ColumnLayout {

        QLabel {
            text: root.text
        }

        QLabel {
            text: "Active " + (root.isActive ? "Yes" : "No")
        }

        QLabel {
            text: "Music"
        }

        QLabel {
            text: "Light"
        }
    }
}
