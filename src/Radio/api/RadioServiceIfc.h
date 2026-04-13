#ifndef SRC_RADIO_API_RADIO_SERVICE_IFC_H
#define SRC_RADIO_API_RADIO_SERVICE_IFC_H

#include <memory>
#include <optional>
#include <vector>

#include "RadioEntity.h"
#include "RadioSearchFilter.h"
#include "RadioSearchResult.h"
#include "RadioSourceProviderIfc.h"
#include "Stream.h"

/**
 * Provider-independent radio service interface.
 */
class RadioServiceIfc {
public:

    virtual ~RadioServiceIfc() = default;

    /**
     * Register a provider-specific radio adapter.
     * @param provider The provider adapter to register.
     */
    virtual void registerProvider(std::shared_ptr<RadioSourceProviderIfc> provider) = 0;

    /**
    * Initialize the service, loading persisted state and notifying listeners.
    */
    virtual void initialize() = 0;

    /**
     * Search radios across registered providers.
     *
     * @note If a search is already in progress, the request is ignored and the
     * returned stream finishes immediately.
     *
     * @param filter The search filter.
     * @return A stream of matching search results.
     */
    virtual Stream<RadioSearchResult> searchRadios(RadioSearchFilter const& filter) = 0;

    /**
     * Add or update a favorite radio.
     * @param radio The radio to persist.
     */
    virtual void addFavorite(RadioEntity const& radio) = 0;

    /**
     * Remove a favorite radio.
     * @param radioId The favorite radio identifier.
     */
    virtual void removeFavorite(RadioId const& radioId) = 0;

    /**
     * Retrieve the stored favorite radios.
     * @return The list of favorite radios.
     */
    virtual std::vector<RadioEntity> favorites() const = 0;

    /**
     * Persist the last selected radio. Pass an empty optional to clear the selection.
     * @param radio The radio to persist, or empty to clear.
     */
    virtual void selectRadio(std::optional<RadioEntity> const& radio) = 0;

    /**
     * Retrieve the last selected radio.
     * @return The currently selected radio, if available.
     */
    virtual std::optional<RadioEntity> selectedRadio() const = 0;
};

#endif // SRC_RADIO_API_RADIO_SERVICE_IFC_H
