import QtQuick

import Ui


QIcon {
    id: networkIcon

    property int strength: 0

    icon: if (strength <= 5) {
        return "\ue2cf"; // no connection
    } else if (strength < 20) {
        return "\uf6aa"; // weak
    } else if (strength < 40) {
        return "\uf6ab"; // medium
    } else if (strength < 80) {
        return "\uf1eb"; // excellent
    } else {
        return "\uf6ac"; // disconnected
    }
}