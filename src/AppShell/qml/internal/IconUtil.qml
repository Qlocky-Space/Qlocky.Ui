pragma Singleton

import QtQuick

QtObject {
    /**
    * Converts a network strength value to an icon.
    * @param {int} strength
    * @returns {string} The icon representation of the network strength.
    */
    function toNetworkStrength(strength) {
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

    /**
     * Converts a volume level to an icon.
     * @param {int} volume
     * @returns {string} The icon representation of the volume level.
     */
    function toVolume(volume) {
        if (volume <= 0) {
            return "\uf6a9"; // mute
        } else if (volume < 20) {
            return "\uf026"; // low volume
        } else if (volume < 40) {
            return "\uf027"; // medium volume
        } else if (volume < 70) {
            return "\uf6a8"; // high volume
        } else {
            return "\uf028"; // max volume
        }
    }

    /**
     * Converts a volume type to an icon.
     * @param {VolumeType} type
     * @returns {string} The icon representation of the volume type.
     */
    function toVolumeType(type, volume) {
        switch (type) {
            case VolumeType.Mute:
                return "\uf2e2";
            case VolumeType.Vibration:
                return "\ue33d";
            case VolumeType.Acoustic:
                return toVolume(volume);
            default:
                return "\uf2e2"; // default to mute
        }
    }

    /**
     * Converts a volume type to a boolean indicating if the volume is active.
     * @param {VolumeType} type
     * @returns {boolean} True if the volume is active, false otherwise.
     */
    function toVolumeTypeStatus(type) {
        switch (type) {
            case VolumeType.Mute:
                return false
            case VolumeType.Vibration:
                return true
            case VolumeType.Acoustic:
                return true
            default:
                return false
        }
    }
}

