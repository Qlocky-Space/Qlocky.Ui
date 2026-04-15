#ifndef SRC_RADIO_INTERNAL_RADIO_BROWSER_PROVIDER_H
#define SRC_RADIO_INTERNAL_RADIO_BROWSER_PROVIDER_H

#include <memory>
#include <RestApi.h>

#include "RadioBrowserAPIv1.h"
#include "RadioSourceProviderIfc.h"

/**
 * Radio source provider backed by the radio-browser.info API.
 *
 * Searches directly against the radio-browser.info REST API and maps each
 * returned record into a RadioSearchResult. Results are emitted in batches to
 * keep the event loop responsive under large payloads.
 */
class RadioBrowserProvider final : public RadioSourceProviderIfc {
public:

    /**
     * Create the provider.
     * @param restApi REST client used to contact the radio-browser.info API.
     */
    explicit RadioBrowserProvider(RestApi& restApi);

    /**
     * Destroy the provider.
     */
    ~RadioBrowserProvider() final = default;

    /**
     * @see RadioSourceProviderIfc::providerId
     */
    std::string providerId() const final;

    /**
     * @see RadioSourceProviderIfc::searchRadios
     */
    Stream<RadioSearchResult> searchRadios(RadioSearchFilter const& filter) final;

    /**
     * @see RadioSourceProviderIfc::findRadioByProviderId
     */
    Task<std::optional<RadioEntity>> findRadioByProviderId(std::string const& providerRadioId) final;

private:

    void handleSearchResponse(
        Result<RadioBrowserAPIv1, RestApiCode> const& result,
        Stream<RadioSearchResult>::Observer const& observer);
    Task<void> searchRadiosAsync(
        RestApiRequestOptions options,
        Stream<RadioSearchResult>::Observer observer);
    void emitBatch(
        std::shared_ptr<std::vector<RadioSearchResult>> const& results,
        std::size_t nextIndex,
        Stream<RadioSearchResult>::Observer const& observer) const;
    RadioSearchResult toSearchResult(RadioBrowserApiStationRecord const& record) const;
    std::string createSearchUrl(RadioSearchFilter const& filter) const;

    RestApi& m_restApi;
};

#endif // SRC_RADIO_INTERNAL_RADIO_BROWSER_PROVIDER_H
