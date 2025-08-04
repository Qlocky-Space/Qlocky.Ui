#ifndef NETWORK_STATE_TYPE_H
#define NETWORK_STATE_TYPE_H

#include <QObject>

#include "events/WifiStatusEvent.h"

/**
 * NetworkStateType is an enumeration representing the different states of network connectivity.
 */
class NetworkStateType : public QObject {
    Q_OBJECT

public:

    enum class State {
        Disabled,
        Connected,
        Searching,
        Disconnected,
        Error,
    };
    Q_ENUM(State)
};

namespace {
constexpr NetworkStateType::State toNetworkType(WifiStatus status) {
    switch (status) {
        case WifiStatus::UP:
            return NetworkStateType::State::Disconnected;
        case WifiStatus::DOWN:
            return NetworkStateType::State::Disabled;
        case WifiStatus::CONNECTING:
            return NetworkStateType::State::Searching;
        case WifiStatus::CONNECTED:
            return NetworkStateType::State::Connected;
        case WifiStatus::ERROR:
            return NetworkStateType::State::Error;
        default:
            return NetworkStateType::State::Error;
    }
}
} // namespace

#endif