import QtQuick 

Text {
    id: root

    readonly property bool isEmpty: text.length === 0

    color: ThemeManager.theme.labelPrimary

    elide: Text.ElideRight
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter

    font {
        family: FontStyle.caption.family
        pixelSize: FontStyle.caption.pixelSize
    }
}