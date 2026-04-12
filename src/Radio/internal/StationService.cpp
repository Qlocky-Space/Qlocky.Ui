#include "StationService.h"

#include <ng-log/logging.h>

void StationService::registerProvider(std::shared_ptr<StationProviderIfc> provider) {
    if (!provider) {
        return;
    }

    auto it = std::find_if(m_providers.begin(), m_providers.end(), [&provider](auto const& currentProvider) {
        return currentProvider.get() == provider.get();
    });
    if (it == m_providers.end()) {
        m_providers.push_back(std::move(provider));
    }
}

Stream<StationEntity> StationService::searchStations(StationFilter const& filter) {
    return Stream<StationEntity> {[this, filter](Stream<StationEntity>::Observer const& observer) {
        if (m_providers.empty() || filter.isEmpty()) {
            observer.finish();
            return;
        }

        auto pendingProviders = std::make_shared<std::size_t>(m_providers.size());

        for (std::shared_ptr<StationProviderIfc> const& provider : m_providers) {
            provider->streamStations(filter).consume(
                [observer](StationEntity const& station) {
                    observer.publish(station);
                },
                [observer, pendingProviders]() {
                    observer.finish();
                });
        }
    }};
}
