pragma Singleton

import QtQuick

QtObject {
    /**
    * Converts a network strength value to an icon.
    * @param {int} strength
    * @returns {string} The icon representation of the network strength.
    */
    function toNetwork(state, strength) {
        switch (state) {
            case NetworkStateType.Disconnected:
                return "\uf6ac";
            case NetworkStateType.Connected:
                return toNetworkStrength(strength);
            case NetworkStateType.Searching:
                return "\uf002";
            case NetworkStateType.Error:
                return "\uf071";
            case NetworkStateType.Disabled:
                return "\uf6ac";

            default:
                return "\uf071"; // default to error icon
        }
    }

    /**
     * Converts a network strength value to an icon.
     * @param {int} strength
     * @returns {string} The icon representation of the network strength.
     */
    function toNetworkStrength(strength) {
        // value closer to zero means stronger signal
        // theoretical limits are 0-100, but we use 0-80 for practical purposes
        strength = Math.abs(strength);

        if (strength < 50) {
            return "\uf1eb"; // excellent
        } else if (strength < 65) {
            return "\uf6ab\uf1eb"; // medium
        } else if (strength < 80) {
            return "\uf6aa\uf1eb"; // weak
        } else {
            return "\uf071"; // error
        }
    }
}

