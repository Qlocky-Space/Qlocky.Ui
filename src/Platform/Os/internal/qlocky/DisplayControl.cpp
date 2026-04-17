#include "DisplayControl.h"

#include <chrono>
#include <fstream>
#include <ng-log/logging.h>
#include <string>
#include <thread>

namespace {

constexpr char DISPLAY_POWER_DBUS_SERVICE[] {"ch.qlocky.DisplayPower"};
constexpr char DISPLAY_POWER_DBUS_OBJECT_PATH[] {"/ch/qlocky/DisplayPower"};
constexpr char DISPLAY_POWER_DBUS_INTERFACE[] {"ch.qlocky.DisplayPower1"};
constexpr char DBUS_SERVICE[] {"org.freedesktop.DBus"};
constexpr char DBUS_OBJECT_PATH[] {"/org/freedesktop/DBus"};
constexpr char DBUS_INTERFACE[] {"org.freedesktop.DBus"};
constexpr char DBUS_ERROR_SERVICE_UNKNOWN[] {"org.freedesktop.DBus.Error.ServiceUnknown"};
constexpr char DBUS_ERROR_NAME_HAS_NO_OWNER[] {"org.freedesktop.DBus.Error.NameHasNoOwner"};

constexpr std::size_t DISPLAY_POWER_MAX_RETRIES {25};
constexpr auto DISPLAY_POWER_RETRY_DELAY {std::chrono::milliseconds(200)};

std::string toWestonOutputName(std::string const& drmConnectorName) {
    // DRM connector names are usually prefixed with card index, e.g. card0-HDMI-A-1.
    // Weston output names omit the card prefix and keep the full connector name.
    std::size_t const separatorPosition {drmConnectorName.find('-')};
    if (separatorPosition == std::string::npos || separatorPosition + 1 >= drmConnectorName.size()) {
        return drmConnectorName;
    }

    return drmConnectorName.substr(separatorPosition + 1);
}

bool isServiceNotReadyError(sdbus::Error const& error) {
    std::string const errorName {error.getName()};
    return errorName == DBUS_ERROR_SERVICE_UNKNOWN || errorName == DBUS_ERROR_NAME_HAS_NO_OWNER;
}

} // namespace

DisplayControl::DisplayControl() {
    m_connection = sdbus::createSystemBusConnection();
    m_dbusProxy = sdbus::createProxy(*m_connection,
        sdbus::ServiceName {DBUS_SERVICE},
        sdbus::ObjectPath {DBUS_OBJECT_PATH});
    m_powerProxy = sdbus::createProxy(*m_connection,
        sdbus::ServiceName {DISPLAY_POWER_DBUS_SERVICE},
        sdbus::ObjectPath {DISPLAY_POWER_DBUS_OBJECT_PATH});

    if (!detectDrmConnector()) {
        LOG(WARNING) << "DisplayControl: No connected DRM connector found in /sys/class/drm";
    }
}

DisplayControl::~DisplayControl() = default;

bool DisplayControl::detectDrmConnector() {
    std::error_code error {};
    std::filesystem::path const drmPath {"/sys/class/drm"};

    if (!std::filesystem::exists(drmPath, error)) {
        LOG(WARNING) << "DisplayControl: DRM sysfs path not found: " << drmPath.string();
        return false;
    }

    for (std::filesystem::directory_entry const& entry : std::filesystem::directory_iterator(drmPath, error)) {
        if (error) {
            continue;
        }

        std::string const name {entry.path().filename().string()};
        if (name.find("HDMI") == std::string::npos && name.find("DP") == std::string::npos) {
            continue;
        }

        std::filesystem::path const statusPath {entry.path() / "status"};
        if (!std::filesystem::exists(statusPath, error)) {
            continue;
        }

        std::ifstream statusFile {statusPath};
        if (!statusFile.is_open()) {
            continue;
        }

        std::string status;
        std::getline(statusFile, status);

        if (status == "connected") {
            m_drmConnectorStatusPath = statusPath;
            m_outputName = toWestonOutputName(name);
            LOG(INFO) << "DisplayControl: Using DRM connector: " << statusPath.string();
            return true;
        }
    }

    return false;
}

bool DisplayControl::requestPowerState(char const* methodName, char const* requestedState) {
    if (!waitForPowerService()) {
        logUnavailablePowerService(requestedState, "The name ch.qlocky.DisplayPower was not provided by any .service files");
        return false;
    }

    for (std::size_t attempt {0}; attempt < DISPLAY_POWER_MAX_RETRIES; ++attempt) {
        try {
            m_powerProxy->callMethod(methodName)
                .onInterface(DISPLAY_POWER_DBUS_INTERFACE)
                .withArguments(m_outputName);

            if (!m_hasLoggedPowerServiceAvailable) {
                m_hasLoggedPowerServiceAvailable = true;
                LOG(INFO) << "DisplayControl: Display power service is available on DBus";
            }

            return true;
        }
        catch (sdbus::Error const& error) {
            if (!isServiceNotReadyError(error) || attempt + 1 >= DISPLAY_POWER_MAX_RETRIES) {
                logUnavailablePowerService(requestedState, error.getMessage());
                return false;
            }

            std::this_thread::sleep_for(DISPLAY_POWER_RETRY_DELAY);
        }
    }

    return false;
}

bool DisplayControl::requestDim(uint8_t level) {
    if (!waitForPowerService()) {
        logUnavailablePowerService("dim", "The name ch.qlocky.DisplayPower was not provided by any .service files");
        return false;
    }

    try {
        m_powerProxy->callMethod("SetDimLevel")
            .onInterface(DISPLAY_POWER_DBUS_INTERFACE)
            .withArguments(m_outputName, static_cast<uint32_t>(level));

        return true;
    }
    catch (sdbus::Error const& error) {
        logUnavailablePowerService("dim", error.getMessage());
        return false;
    }
}

bool DisplayControl::waitForPowerService() {
    for (std::size_t attempt {0}; attempt < DISPLAY_POWER_MAX_RETRIES; ++attempt) {
        try {
            bool hasOwner {false};
            m_dbusProxy->callMethod("NameHasOwner")
                .onInterface(DBUS_INTERFACE)
                .withArguments(std::string {DISPLAY_POWER_DBUS_SERVICE})
                .storeResultsTo(hasOwner);

            if (hasOwner) {
                if (!m_powerServiceConnected) {
                    m_powerServiceConnected = true;
                    m_hasLoggedUnavailablePowerService = false;
                    LOG(INFO) << "DisplayControl: Power service connected, ensuring display is on";
                    m_powerProxy->callMethod("TurnOn")
                        .onInterface(DISPLAY_POWER_DBUS_INTERFACE)
                        .withArguments(m_outputName);
                }
                return true;
            }
        }
        catch (sdbus::Error const&) {
            // Retry until timeout. If DBus is temporarily unavailable, a later
            // attempt may still succeed during startup.
        }

        std::this_thread::sleep_for(DISPLAY_POWER_RETRY_DELAY);
    }

    m_powerServiceConnected = false;
    return false;
}

void DisplayControl::logUnavailablePowerService(char const* requestedState, std::string const& errorMessage) {
    if (m_hasLoggedUnavailablePowerService) {
        return;
    }

    m_hasLoggedUnavailablePowerService = true;

    LOG(WARNING) << "DisplayControl: Failed to forward display power request (" << requestedState
                 << ") for output " << m_outputName
                 << " to DBus service " << DISPLAY_POWER_DBUS_SERVICE
                 << ": " << errorMessage;
}

void DisplayControl::turnOn() {
    if (m_drmConnectorStatusPath.empty()) {
        LOG(WARNING) << "DisplayControl: Cannot turn on - no DRM connector available";
        return;
    }

    LOG(INFO) << "DisplayControl: Turning display on";
    requestPowerState("TurnOn", "on");
}

void DisplayControl::turnOff() {
    if (m_drmConnectorStatusPath.empty()) {
        LOG(WARNING) << "DisplayControl: Cannot turn off - no DRM connector available";
        return;
    }

    LOG(INFO) << "DisplayControl: Turning display off";
    requestPowerState("TurnOff", "off");
}

void DisplayControl::dim(uint8_t level) {
    if (m_drmConnectorStatusPath.empty()) {
        LOG(WARNING) << "DisplayControl: Cannot dim - no DRM connector available";
        return;
    }

    LOG(INFO) << "DisplayControl: Dimming display to level " << static_cast<int>(level);
    requestDim(level);
}
