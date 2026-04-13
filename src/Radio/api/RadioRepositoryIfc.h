#ifndef SRC_RADIO_API_RADIO_REPOSITORY_IFC_H
#define SRC_RADIO_API_RADIO_REPOSITORY_IFC_H

#include <optional>
#include <vector>

#include "RadioEntity.h"

/**
 * Radio repository interface.
 *
 * This repository stores the user's favorite radios and the last selected radio.
 */
class RadioRepositoryIfc {
public:

    virtual ~RadioRepositoryIfc() = default;

    /**
     * Initialize the repository.
     */
    virtual void initialize() = 0;

    /**
     * Add or update a favorite radio in the repository.
     * @param radio The radio entity to store.
     */
    virtual void addFavorite(RadioEntity const& radio) = 0;

    /**
     * Remove a favorite radio from the repository.
     * @param radioId The radio identifier to remove.
     */
    virtual void removeFavorite(RadioId const& radioId) = 0;

    /**
     * Retrieve one favorite radio by identifier.
     * @param radioId The radio identifier to look up.
     * @return The matching radio, if found.
     */
    virtual std::optional<RadioEntity> getFavorite(RadioId const& radioId) const = 0;

    /**
     * Retrieve all favorite radios.
     * @return All stored favorite radios.
     */
    virtual std::vector<RadioEntity> getFavorites() const = 0;

    /**
     * Persist the last selected radio. Pass an empty optional to clear the selection.
     * @param radio The radio entity to persist as selected, or empty to clear.
     */
    virtual void setLastSelected(std::optional<RadioEntity> const& radio) = 0;

    /**
     * Retrieve the last selected radio.
     * @return The last selected radio, if available.
     */
    virtual std::optional<RadioEntity> getLastSelected() const = 0;
};

#endif // SRC_RADIO_API_RADIO_REPOSITORY_IFC_H
