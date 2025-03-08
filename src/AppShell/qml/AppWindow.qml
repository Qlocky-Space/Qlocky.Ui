import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AppShell 1.0

ApplicationWindow {
    id: root
    visible: true
    color: 'black'
    width: 1920
    height: 1080

    property MainWindowViewModel mainWindowViewModel

    MainWindowViewModel {
        id: viewModel
        window: root
    }

    MyScreen {}
}
