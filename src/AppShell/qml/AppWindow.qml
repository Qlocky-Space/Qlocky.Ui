import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Qlocky.Components 1.0

ApplicationWindow {
    id: root
    visible: true
    color: 'black'
    width: 500
    height: 500

    property MainWindowViewModel mainWindowViewModel

    MainWindowViewModel {
        id: viewModel
        window: root
    }

    MyScreen {}
}
