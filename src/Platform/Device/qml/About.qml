import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Shapes

import Ui
import Configuration


ColumnLayout {
    property var viewModel: AboutViewModel

    anchors.fill: parent

    SettingGroup {
        id: productGroup
        Layout.fillWidth: true

        title: qsTr("Product")

        SettingKeyValueItem {
            title: qsTr("Product Name")
            value: viewModel.productName
        }
        SettingKeyValueItem {
            title: qsTr("Model")
            value: viewModel.deviceModel
        }
        SettingKeyValueItem {
            title: qsTr("Serial Number")
            value: viewModel.serialNumber
        }
    }

    SettingGroup {
        id: appIdentificationGroup
        Layout.fillWidth: true

        title: qsTr("App identifiers")

        SettingKeyValueItem {
            function formatUptime(seconds) {
                if (seconds === undefined || seconds === null || isNaN(seconds))
                    return "";

                seconds = Math.floor(seconds);
                var h = Math.floor(seconds / 3600);
                var m = Math.floor((seconds % 3600) / 60);
                var s = seconds % 60;

                var result = ""
                result += (h > 0 ? h + ":" : "")
                result += (m < 10 ? "0" : "") + m + ":"
                result += (s < 10 ? "0" : "") + s

                return result;
            }

            title: qsTr("Uptime")
            value: formatUptime(viewModel.upTime)
        }
        SettingKeyValueItem {
            title: qsTr("App Version")
            value: viewModel.appVersion
        }
        SettingKeyValueItem {
            title: qsTr("App Build number")
            value: viewModel.appBuildNumber
        }
    }

    SettingGroup {
        id: osIdentificationGroup
        Layout.fillWidth: true

        title: qsTr("OS identifiers")

        SettingKeyValueItem {
            title: qsTr("Kernel Version")
            value: viewModel.kernelVersion
        }
        SettingKeyValueItem {
            title: qsTr("Kernel Build Date")
            value: viewModel.kernelBuildDate
            valueLabel.font.pixelSize: 24
        }
    }

    SettingGroup {
        id: legalRightsGroup
        Layout.fillWidth: true

        title: qsTr("Legal and regulatory")

        SettingKeyValueItem {
            title: qsTr("Third-party licences")
            value: "Qlocky Wiki"
            clickable: true
            onClicked: {
                CommandExecutor.dispatch("show-qr-code", { "content": "https://qlocky.notion.site/Qlocky-Wiki-b2c1fdab6b84481caad0c45b414d6cd8" })
            }
        }
        SettingKeyValueItem {
            title: qsTr("Source code")
            value: "Qlocky GitHub"
            clickable: true
            onClicked: {
                CommandExecutor.dispatch("show-qr-code", { "content": "https://www.github.com/Qlocky-Space" })
            }
        }
    }
}