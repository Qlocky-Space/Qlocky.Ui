#ifndef WPA_SUPPLICANT_HELPER_H
#define WPA_SUPPLICANT_HELPER_H

#include <cinttypes>

class WpaSupplicantHelper {
public:

    /**
     * Unblocks a specific rfkill device.
     * This method writes to the /dev/rfkill device to unblock the specified rfkill
     * device by index. The index is typically 1 for Wi-Fi.
     * @param index The index of the rfkill device to unblock.
     * @note This method requires root privileges to write to /dev/rfkill.
     */
    static void unblockRfkillDevice(uint32_t const index);

    /**
     * Blocks a specific rfkill device.
     * This method writes to the /dev/rfkill device to block the specified rfkill
     * device by index. The index is typically 1 for Wi-Fi.
     * @param index The index of the rfkill device to block.
     * @note This method requires root privileges to write to /dev/rfkill.
     */
    static void blockRfkillDevice(uint32_t const index);

    /**
     * Checks if the wpa_supplicant process is running.
     */
    static bool wpaSupplicantIsRunning();
};

#endif