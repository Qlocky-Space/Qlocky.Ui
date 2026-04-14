#include "RadioService.h"

#include <algorithm>
#include <memory>
#include <unordered_set>

#include "events/RadioSelectionChangedEvent.h"

RadioService::RadioService(RadioRepositoryIfc& repository, Mediator& mediator) :
    m_repository {repository},
    m_mediator {mediator} {
}

void RadioService::registerProvider(std::shared_ptr<RadioSourceProviderIfc> provider) {
    if (!provider) {
        return;
    }

    auto const it = std::find_if(m_providers.begin(), m_providers.end(), [&provider](std::shared_ptr<RadioSourceProviderIfc> const& currentProvider) {
        return currentProvider->providerId() == provider->providerId();
    });
    if (it == m_providers.end()) {
        m_providers.push_back(std::move(provider));
    }
}

Stream<RadioSearchResult> RadioService::searchRadios(RadioSearchFilter const& filter) {
    return Stream<RadioSearchResult> {[this, filter](Stream<RadioSearchResult>::Observer const& observer) {
        if (m_searchInProgress) {
            observer.finish();
            return;
        }

        if (filter.isEmpty() || m_providers.empty()) {
            observer.finish();
            return;
        }

        m_searchInProgress = true;

        auto seenRadioIds = std::make_shared<std::unordered_set<std::string>>();
        auto pendingProviders = std::make_shared<std::size_t>(m_providers.size());

        for (std::shared_ptr<RadioSourceProviderIfc> const& provider : m_providers) {
            provider->searchRadios(filter).consume(
                [seenRadioIds, observer](RadioSearchResult const& result) {
                    if (result.radio.id.empty()) {
                        return;
                    }

                    if (!seenRadioIds->insert(result.radio.id).second) {
                        return;
                    }

                    observer.publish(result);
                },
                [this, observer, pendingProviders]() {
                    if (*pendingProviders == 0) {
                        return;
                    }

                    --(*pendingProviders);
                    if (*pendingProviders == 0) {
                        m_searchInProgress = false;
                        observer.finish();
                    }
                });
        }
    }};
}

void RadioService::initialize() {
    selectRadio(m_repository.getLastSelected());
}

void RadioService::addFavorite(RadioEntity const& radio) {
    m_repository.addFavorite(radio);
}

void RadioService::removeFavorite(RadioId const& radioId) {
    m_repository.removeFavorite(radioId);
}

std::vector<RadioEntity> RadioService::favorites() const {
    return m_repository.getFavorites();
}

void RadioService::selectRadio(std::optional<RadioEntity> const& radio) {
    m_repository.setLastSelected(radio);
    m_mediator.notify(RadioSelectionChangedEvent {radio});
}

std::optional<RadioEntity> RadioService::selectedRadio() const {
    return m_repository.getLastSelected();
}

Task<std::optional<RadioEntity>> RadioService::resolveRadioById(RadioId const& radioId) {
    if (radioId.empty()) {
        co_return std::nullopt;
    }

    auto const selected = m_repository.getLastSelected();
    if (selected.has_value() && selected->id == radioId) {
        co_return selected;
    }

    auto const favorite = m_repository.getFavorite(radioId);
    if (favorite.has_value()) {
        co_return favorite;
    }

    std::size_t const separatorIndex {radioId.find(':')};
    if (separatorIndex == std::string::npos || separatorIndex == 0 || (separatorIndex + 1) >= radioId.size()) {
        co_return std::nullopt;
    }

    std::string const providerId {radioId.substr(0, separatorIndex)};
    std::string const providerRadioId {radioId.substr(separatorIndex + 1)};

    auto const providerIt = std::find_if(m_providers.begin(), m_providers.end(), [&providerId](std::shared_ptr<RadioSourceProviderIfc> const& provider) {
        return provider && provider->providerId() == providerId;
    });
    if (providerIt == m_providers.end()) {
        co_return std::nullopt;
    }

    co_return co_await(*providerIt)->findRadioByProviderId(providerRadioId);
}
