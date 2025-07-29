#ifndef NETWORK_REPOSITORY_H
#define NETWORK_REPOSITORY_H

#include <Mediator.h>
#include <PersistenceKey.h>
#include <PersistenceServiceIfc.h>
#include <vector>

#include "NetworkRepositoryIfc.h"

/**
 * @see NetworkRepositoryIfc
 *
 * This repository manages network profiles and persists them using the PersistenceServiceIfc.
 */
class NetworkRepository : public NetworkRepositoryIfc {
public:

    NetworkRepository(Mediator& mediator, PersistenceServiceIfc& persistency);

    /**
     * @see NetworkRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see NetworkRepositoryIfc::addProfile
     */
    void addProfile(NetworkProfileEntity const& profile) final;

    /**
     * @see NetworkRepositoryIfc::getProfile
     */
    void removeProfile(std::string const& ssid) final;

    /**
     * @see NetworkRepositoryIfc::getProfileById
     */
    std::optional<NetworkProfileEntity> getProfileBySsid(std::string const& ssid) final;

    /**
     * @see NetworkRepositoryIfc::setNetworkEnabled
     */
    void setNetworkEnabled(bool enabled) final;

    /**
     * @see NetworkRepositoryIfc::getNetworkEnabled
     */
    bool getNetworkEnabled() final;

    /**
     * @see NetworkRepositoryIfc::setAirplaneMode
     */
    void setAirplaneMode(bool enabled) final;

    /**
     * @see NetworkRepositoryIfc::getAirplaneMode
     */
    bool getAirplaneMode() final;

    /**
     * @see NetworkRepositoryIfc::getProfile
     */
    std::vector<NetworkProfileEntity> getAllProfiles() const final {
        return m_networkProfiles;
    }

private:

    static std::string const NETWORK_NAMESPACE;

    struct Preferences final {
        inline static std::string const NetworksKey {"Networks"};
        inline static PersistenceKey const AirplaneModeKey {"AirplaneMode"};
        inline static PersistenceKey const NetworkEnabledKey {"NetworkEnabled"};
    };

    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(NETWORK_NAMESPACE);
    }

    ResultVoid updateObject(NetworkProfileEntity const& profile);
    ResultVoid removeObject(uint32_t const profileId);

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
    std::vector<NetworkProfileEntity> m_networkProfiles;
};

#endif