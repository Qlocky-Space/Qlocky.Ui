import QtQuick

import Ui

QIcon {
    id: networkIcon



    property int strength: 0

    icon: IconUtil.toIcon(strength)
}