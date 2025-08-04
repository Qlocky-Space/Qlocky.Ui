#include "WpaSupplicantHelper.h"

#include <algorithm>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/rfkill.h>
#include <ng-log/logging.h>
#include <unistd.h>

namespace {

static inline void setRfkillState(uint32_t const index, bool const block) {
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
        LOG(INFO) << "rfkill " << index << " " << (block ? "blocked" : "unblocked") << " via /dev/rfkill";
    }

    close(fd);
}

static inline std::vector<std::string> getCmdLineArgs(pid_t pid) {
    std::vector<std::string> args;
    std::string path = "/proc/" + std::to_string(pid) + "/cmdline";
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return args;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    size_t start = 0;
    for (size_t i = 0; i < content.size(); ++i) {
        if (content[i] == '\0') {
            args.emplace_back(&content[start], &content[i]);
            start = i + 1;
        }
    }

    return args;
}

static inline bool isWpaRunning(std::string const& name, std::initializer_list<std::string> const& expectedArgs = {}) {
    DIR* proc = opendir("/proc");
    if (!proc) {
        return false;
    }

    struct dirent* entry;
    while ((entry = readdir(proc)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            char const* dname = entry->d_name;
            if (std::all_of(dname, dname + std::strlen(dname), ::isdigit)) {
                pid_t pid = std::stoi(dname);
                auto args = getCmdLineArgs(pid);

                if (!args.empty() && args[0].find(name) != std::string::npos) {

                    bool has_args {true};

                    for (auto const& arg : expectedArgs) {
                        if (std::find(args.begin(), args.end(), arg) == args.end()) {
                            has_args = false;
                            break;
                        }
                    }

                    return has_args;
                }
            }
        }
    }

    closedir(proc);
    return false;
}

} // namespace

void WpaSupplicantHelper::unblockRfkillDevice(uint32_t const index) {
    setRfkillState(index, false);
}

void WpaSupplicantHelper::blockRfkillDevice(uint32_t const index) {
    setRfkillState(index, true);
}

bool WpaSupplicantHelper::wpaSupplicantIsRunning() {
    return isWpaRunning("wpa_supplicant", {"-u", "-c"});
}
