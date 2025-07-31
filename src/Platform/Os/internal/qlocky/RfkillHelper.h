#ifndef RFKILL_HELPER_H
#define RFKILL_HELPER_H

#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/rfkill.h>
#include <unistd.h>

class RfkillHelper {
public:

    /**
     * Unblocks a specific rfkill device.
     * This method writes to the /dev/rfkill device to unblock the specified rfkill
     * device by index. The index is typically 1 for Wi-Fi.
     * @param index The index of the rfkill device to unblock.
     * @note This method requires root privileges to write to /dev/rfkill.
     */
    static void unblockRfkillDevice(uint32_t const index) {
        setRfkillState(index, false);
    }

    /**
     * Blocks a specific rfkill device.
     * This method writes to the /dev/rfkill device to block the specified rfkill
     * device by index. The index is typically 1 for Wi-Fi.
     * @param index The index of the rfkill device to block.
     * @note This method requires root privileges to write to /dev/rfkill.
     */
    static void blockRfkillDevice(uint32_t const index) {
        setRfkillState(index, true);
    }

private:

    static void setRfkillState(uint32_t const index, bool const block) {
        int fd = open("/dev/rfkill", O_WRONLY);
        if (fd < 0) {
            perror("open");
            return;
        }

        rfkill_event event {};
        event.idx = index; // Usually 1 for Wi-Fi
        event.type = RFKILL_TYPE_WLAN;
        event.op = RFKILL_OP_CHANGE;
        event.soft = block ? 1 : 0; // 0 = unblocked, 1 = blocked

        ssize_t result = write(fd, &event, sizeof(event));
        if (result < 0) {
            perror("write");
        }
        else {
            std::cout << "rfkill " << index << " " << (block ? "blocked" : "unblocked") << " via /dev/rfkill" << std::endl;
        }

        close(fd);
    }
};

#endif