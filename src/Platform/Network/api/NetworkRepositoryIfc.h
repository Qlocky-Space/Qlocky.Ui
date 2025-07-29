#ifndef NETWORK_REPOSITORY_IFC_H
#define NETWORK_REPOSITORY_IFC_H

#include <optional>
#include <string>

#include "NetworkProfileEntity.h"

/**
 * NetworkRepositoryIfc is an interface for managing network profiles.
 * This interface defines the basic operations for managing network profiles.
 *
 * The implementation of this interface should handle the storage and retrieval of network profiles.
 */
class NetworkRepositoryIfc {
public:

    virtual ~NetworkRepositoryIfc() = default;

    /**
     * Initializes the repository.
     * This method should be called to set up any necessary state or data structures.
     */
    virtual void initialize() = 0;

    /**
     * Adds a new network profile to the repository.
     * @param profile The network profile entity to add.
     */
    virtual void addProfile(NetworkProfileEntity const& profile) = 0;

    /**
     * Removes a network profile from the repository.
     * @param ssid The SSID of the network profile to remove.
     */
    virtual void removeProfile(std::string const& ssid) = 0;

    /**
     * Retrieves a network profile by its ID.
     * @param ssid The SSID of the network profile to retrieve.
     * @return An optional containing the network profile entity if found, or empty if not found
     */
    virtual std::optional<NetworkProfileEntity> getProfileBySsid(std::string const& ssid) = 0;

    /**
     * Sets the network enabled state.
     * @param enabled True to enable the network, false to disable it.
     */
    virtual void setNetworkEnabled(bool enabled) = 0;

    /**
     * Retrieves the network enabled state.
     * @return True if the network is enabled, false otherwise.
     */
    virtual bool getNetworkEnabled() = 0;

    /**
     * Sets the airplane mode state.
     * @param enabled True to enable airplane mode, false to disable it.
     */
    virtual void setAirplaneMode(bool enabled) = 0;

    /**
     * Retrieves the airplane mode state.
     * @return True if airplane mode is enabled, false otherwise.
     */
    virtual bool getAirplaneMode() = 0;

    /**
     * Retrieves all network profiles from the repository.
     * @return A vector containing all network profile entities.
     */
    virtual std::vector<NetworkProfileEntity> getAllProfiles() const = 0;
};

#endif
