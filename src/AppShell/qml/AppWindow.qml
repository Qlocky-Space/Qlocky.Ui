import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AppShell 1.0

ApplicationWindow {
    id: root
    visible: true
    color: "#16171A"
    width: 1920
    height: 1080

    property MainWindowViewModel mainWindowViewModel

    menuBar: StatusBar {}

    MainWindowViewModel {
        id: viewModel
        window: root
    }

    WindowContent {}
}
