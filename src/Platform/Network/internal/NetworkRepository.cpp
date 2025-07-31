#include "NetworkRepository.h"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>

#include "events/NetworkProfileAddedEvent.h"
#include "events/NetworkProfileRemovedEvent.h"
#include "events/NetworkProfileUpdatedEvent.h"

std::string const NetworkRepository::NETWORK_NAMESPACE {"Network"};

NetworkRepository::NetworkRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator(mediator),
    m_persistency(persistency) {
}

void NetworkRepository::initialize() {
    m_networkProfiles.clear();

    auto results {getContext().getList(Preferences::NetworksKey)};
    if (results.isError()) {
        // TODO log error
        std::cerr << "Failed to get network profiles: " << results.error() << std::endl;
        return;
    }

    for (auto const& [key, value] : results.value()) {
        // TODO log error - handle exception
        auto json = nlohmann::json::parse(value);
        auto profile = json.get<NetworkProfileEntity>();
        m_networkProfiles.push_back(profile);
        m_mediator.notify(NetworkProfileAddedEvent {profile});
    }
}

void NetworkRepository::addProfile(NetworkProfileEntity const& profile) {
    auto it = std::find_if(m_networkProfiles.begin(), m_networkProfiles.end(),
        [&profile](NetworkProfileEntity const& p) { return p.id == profile.id; });

    ResultVoid const result {updateObject(profile)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to update networkprofile: " << result.error() << std::endl;
        return;
    }

    if (it != m_networkProfiles.end()) {
        *it = profile;
        m_mediator.notify(NetworkProfileUpdatedEvent {profile});
    }
    else {
        m_networkProfiles.push_back(profile);
        m_mediator.notify(NetworkProfileAddedEvent {profile});
    }
}

void NetworkRepository::removeProfile(std::string const& ssid) {
    auto it = std::find_if(m_networkProfiles.begin(), m_networkProfiles.end(),
        [&ssid](NetworkProfileEntity const& p) { return p.ssid == ssid; });
    ProfileId const id = it != m_networkProfiles.end() ? it->id : 0;

    m_networkProfiles.erase(
        std::remove_if(m_networkProfiles.begin(), m_networkProfiles.end(),
            [ssid](NetworkProfileEntity const& p) {
                return p.ssid == ssid;
            }),
        m_networkProfiles.end());

    ResultVoid const result {removeObject(id)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to remove network profile: " << result.error() << std::endl;
        return;
    }

    m_mediator.notify(NetworkProfileRemovedEvent {id});
}

void NetworkRepository::selectNetwork(std::string const& ssid) {
    auto profile = getProfileBySsid(ssid);

    getContext().setString(Preferences::LastNetworkKey, ssid);
}

std::optional<NetworkProfileEntity> NetworkRepository::getLastNetwork() {
    auto lastSsid = getContext().getString(Preferences::LastNetworkKey);
    if (lastSsid.isError()) {
        // Not found, return empty optional
        return std::nullopt;
    }

    return getProfileBySsid(lastSsid.value());
}

std::optional<NetworkProfileEntity> NetworkRepository::getProfileBySsid(std::string const& ssid) {
    auto it = std::find_if(m_networkProfiles.begin(), m_networkProfiles.end(),
        [ssid](NetworkProfileEntity const& p) { return p.ssid == ssid; });

    if (it != m_networkProfiles.end()) {
        return *it;
    }
    return std::nullopt;
}

void NetworkRepository::setNetworkEnabled(bool enabled) {
    getContext().setBool(Preferences::NetworkEnabledKey, enabled);
}

bool NetworkRepository::getNetworkEnabled() {
    return getContext().getBool(Preferences::NetworkEnabledKey).valueOr(false);
}

void NetworkRepository::setAirplaneMode(bool enabled) {
    getContext().setBool(Preferences::AirplaneModeKey, enabled);
}

bool NetworkRepository::getAirplaneMode() {
    return getContext().getBool(Preferences::AirplaneModeKey).valueOr(false);
}

ResultVoid NetworkRepository::updateObject(NetworkProfileEntity const& profile) {
    return getContext().setListItem(Preferences::NetworksKey, profile.id, nlohmann::json(profile).dump());
}

ResultVoid NetworkRepository::removeObject(uint32_t const profileId) {
    return getContext().removeListItem(Preferences::NetworksKey, profileId);
}
