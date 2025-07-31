

#include "SettingPageViewModel.h"

SettingPageViewModel::SettingPageViewModel(NetworkServiceIfc& networkService, NetworkRepositoryIfc& networkRepository) :
    QObject {nullptr},
    m_networkService {networkService},
    m_networkRepository {networkRepository} {
}

// TODO remove demo methods
void SettingPageViewModel::networkDisconnect() {
    m_networkService.disconnect();
}

// TODO remove demo methods
void SettingPageViewModel::networkConnect() {
    std::string const ssid = "XXXXXXXXX";
    std::string const psk = "xxxxxxxx";

    // m_networkRepository.removeProfile(ssid);

    auto profiles {m_networkRepository.getAllProfiles()};
    if (profiles.empty()) {
        NetworkProfileNew profile {};
        profile.Ssid = ssid;
        profile.Psk = psk;
        profile.AutoConnect = true;
        m_networkService.connectTo(profile);
    }
    else {
        m_networkService.connectTo(profiles.front().ssid);
    }
}
