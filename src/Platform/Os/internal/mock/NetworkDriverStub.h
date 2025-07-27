#ifndef OS_NETWORK_DRIVER_STUB_H
#define OS_NETWORK_DRIVER_STUB_H

#include <Subject.h>

#include "NetworkDriverIfc.h"

class NetworkDriverStub : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    NetworkDriverStub() = default;
    ~NetworkDriverStub() override = default;

    ResultVoid up(std::string const& interfaceName) override {
        if (m_isUp) {
            return ResultVoid::success(false);
        }

        m_isUp = true;
        return ResultVoid::success(true);
    }

    ResultVoid down() override {
        if (!m_isUp) {
            return ResultVoid::success(false);
        }

        return ResultVoid::success(true);
    }

    ResultVoid triggerScan() override {
        return ResultVoid::success(m_isUp);
    }

private:

    bool m_isUp {false};
};

#endif