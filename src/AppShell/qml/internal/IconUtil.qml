pragma Singleton

import QtQuick

QtObject {
    /**
    * Converts a network strength value to an icon.
    * @param {int} strength
    * @returns {string} The icon representation of the network strength.
    */
    function toIcon(strength) {
        if (strength <= 5) {
            return "\uf6ac"; // no connection
        } else if (strength < 20) {
            return "\uf6aa"; // weak
        } else if (strength < 40) {
            return "\uf6ab"; // medium
        } else if (strength < 80) {
            return "\uf1eb"; // excellent
        } else {
            return "\ue2cf"; // disconnected
        }
    }
}

