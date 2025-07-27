#include "WpaSupplicantDBusDriver.h"

NetworkResult WpaSupplicantDBusDriver::up(std::string const& interfaceName) {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::down() {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::triggerScan() {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::fetchScanResults() {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::abortScan() {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::connectTo(std::string const& ssid) {
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}