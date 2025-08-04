#include "AboutViewModel.h"

AboutViewModel::AboutViewModel(Mediator& mediator, DeviceInfoProviderIfc& deviceInfo) :
    m_deviceInfoProvider {deviceInfo},
    m_upTimer {this},
    m_upElapsedTimer {} {
    m_upElapsedTimer.start();

    connect(&m_upTimer, &QTimer::timeout, this, [this]() { emit upTimeChanged(); });
    m_upTimer.setInterval(1000); // Update every second
    m_upTimer.start();
}
