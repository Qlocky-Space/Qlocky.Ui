#ifndef SRC_RADIO_API_RADIO_SOURCE_PROVIDER_IFC_H
#define SRC_RADIO_API_RADIO_SOURCE_PROVIDER_IFC_H

#include <functional>
#include <optional>
#include <string>

#include "RadioEntity.h"
#include "RadioSearchFilter.h"
#include "RadioSearchResult.h"
#include "Stream.h"

/**
 * Provider-specific adapter used by the generic radio service.
 * A source provider owns provider-specific search mapping.
 */
class RadioSourceProviderIfc {
public:

    virtual ~RadioSourceProviderIfc() = default;

    /**
     * @return Stable provider identifier used in RadioEntity::provider.
     */
    virtual std::string providerId() const = 0;

    /**
     * Search radios exposed by this provider.
     * @param filter The search filter.
     * @return A stream of provider-specific search results mapped to generic radios.
     */
    virtual Stream<RadioSearchResult> searchRadios(RadioSearchFilter const& filter) = 0;

    /**
     * Resolve one provider-specific radio by provider ID.
     * @param providerRadioId Provider-local radio identifier.
     * @param callback Receives the resolved radio or empty if not found.
     */
    virtual void findRadioByProviderId(std::string const& providerRadioId, std::function<void(std::optional<RadioEntity> const&)> callback) = 0;
};

#endif // SRC_RADIO_API_RADIO_SOURCE_PROVIDER_IFC_H
