#ifndef SRC_RADIO_INTERNAL_RADIO_SERVICE_H
#define SRC_RADIO_INTERNAL_RADIO_SERVICE_H

#include <Mediator.h>
#include <memory>
#include <vector>

#include "RadioRepositoryIfc.h"
#include "RadioServiceIfc.h"

/**
 * Default radio service implementation.
 */
class RadioService final : public RadioServiceIfc {
public:

    /**
     * Create a radio service.
     * @param repository Repository used for favorites and selected radio persistence.
     * @param mediator Event mediator used to publish selection changes.
     */
    RadioService(RadioRepositoryIfc& repository, Mediator& mediator);

    /**
     * Destroy the service.
     */
    ~RadioService() final = default;

    /**
     * @see RadioServiceIfc::registerProvider
     */
    void registerProvider(std::shared_ptr<RadioSourceProviderIfc> provider) final;

    /**
     * @see RadioServiceIfc::searchRadios
     */
    Stream<RadioSearchResult> searchRadios(RadioSearchFilter const& filter) final;

    /**
     * @see RadioServiceIfc::addFavorite
     */
    void addFavorite(RadioEntity const& radio) final;

    /**
     * @see RadioServiceIfc::removeFavorite
     */
    void removeFavorite(RadioId const& radioId) final;

    /**
     * @see RadioServiceIfc::favorites
     */
    std::vector<RadioEntity> favorites() const final;

    /**
     * @see RadioServiceIfc::selectRadio
     */
    void selectRadio(RadioEntity const& radio) final;

    /**
     * @see RadioServiceIfc::selectedRadio
     */
    std::optional<RadioEntity> selectedRadio() const final;

private:

    RadioRepositoryIfc& m_repository;
    Mediator& m_mediator;
    std::vector<std::shared_ptr<RadioSourceProviderIfc>> m_providers {};
    bool m_searchInProgress {false};
};

#endif // SRC_RADIO_INTERNAL_RADIO_SERVICE_H
