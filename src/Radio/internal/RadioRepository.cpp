#include "RadioRepository.h"

#include <nlohmann/json.hpp>

#include "events/RadioFavoriteAddedEvent.h"
#include "events/RadioFavoriteRemovedEvent.h"
#include "events/RadioFavoriteUpdatedEvent.h"

namespace {

[[nodiscard]] nlohmann::json serializeRadio(RadioEntity const& radio) {
    return nlohmann::json {
        {"id", radio.id},
        {"name", radio.name},
        {"provider", radio.provider},
        {"radioId", radio.radioId},
        {"url", radio.url},
        {"iconUrl", radio.iconUrl},
    };
}

[[nodiscard]] RadioEntity deserializeRadio(nlohmann::json const& json) {
    return RadioEntity {
        json.value("id", std::string {}),
        json.value("name", std::string {}),
        json.value("provider", std::string {}),
        json.value("radioId", std::string {}),
        json.value("url", std::string {}),
        json.value("iconUrl", std::string {}),
    };
}

} // namespace

std::string const RadioRepository::RADIO_NAMESPACE {"Radio"};

RadioRepository::RadioRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
    m_favorites.reserve(INITIAL_CAPACITY);
    m_favoriteIndexById.reserve(INITIAL_CAPACITY);
}

void RadioRepository::initialize() {
    m_favorites.clear();
    m_favoriteIndexById.clear();
    m_lastSelected.reset();

    auto const favoritesResult = getContext().getString(Preferences::FAVORITES_KEY);
    if (!favoritesResult.isError() && !favoritesResult.value().empty()) {
        nlohmann::json const favoritesJson = nlohmann::json::parse(favoritesResult.value(), nullptr, false);
        if (favoritesJson.is_array()) {
            for (nlohmann::json const& item : favoritesJson) {
                RadioEntity const radio = deserializeRadio(item);
                if (radio.id.empty()) {
                    continue;
                }

                m_favoriteIndexById.emplace(radio.id, m_favorites.size());
                m_favorites.push_back(radio);
            }
        }
    }

    auto const selectedResult = getContext().getString(Preferences::LAST_SELECTED_KEY);
    if (!selectedResult.isError() && !selectedResult.value().empty()) {
        nlohmann::json const selectedJson = nlohmann::json::parse(selectedResult.value(), nullptr, false);
        if (selectedJson.is_object()) {
            RadioEntity const radio = deserializeRadio(selectedJson);
            if (!radio.id.empty()) {
                m_lastSelected = radio;
            }
        }
    }
}

void RadioRepository::addFavorite(RadioEntity const& radio) {
    auto const it = m_favoriteIndexById.find(radio.id);
    if (it == m_favoriteIndexById.end()) {
        m_favoriteIndexById.emplace(radio.id, m_favorites.size());
        m_favorites.push_back(radio);
        persistFavorites();
        m_mediator.notify(RadioFavoriteAddedEvent {radio});
        return;
    }

    RadioEntity& currentRadio = m_favorites.at(it->second);
    if (!areEqual(currentRadio, radio)) {
        currentRadio = radio;
        persistFavorites();
        m_mediator.notify(RadioFavoriteUpdatedEvent {radio});
    }
}

void RadioRepository::removeFavorite(RadioId const& radioId) {
    auto const it = m_favoriteIndexById.find(radioId);
    if (it == m_favoriteIndexById.end()) {
        return;
    }

    std::size_t const removedIndex {it->second};
    std::size_t const lastIndex {m_favorites.size() - 1};
    if (removedIndex != lastIndex) {
        RadioEntity& movedRadio = m_favorites.at(lastIndex);
        m_favorites.at(removedIndex) = std::move(movedRadio);
        m_favoriteIndexById[m_favorites.at(removedIndex).id] = removedIndex;
    }

    m_favorites.pop_back();
    m_favoriteIndexById.erase(it);
    persistFavorites();
    m_mediator.notify(RadioFavoriteRemovedEvent {radioId});
}

std::optional<RadioEntity> RadioRepository::getFavorite(RadioId const& radioId) const {
    auto const it = m_favoriteIndexById.find(radioId);
    if (it == m_favoriteIndexById.end()) {
        return std::nullopt;
    }

    return m_favorites.at(it->second);
}

void RadioRepository::setLastSelected(std::optional<RadioEntity> const& radio) {
    m_lastSelected = radio;
    persistLastSelected();
}

bool RadioRepository::areEqual(RadioEntity const& lhs, RadioEntity const& rhs) {
    return lhs.id == rhs.id && lhs.name == rhs.name && lhs.provider == rhs.provider && lhs.radioId == rhs.radioId && lhs.url == rhs.url && lhs.iconUrl == rhs.iconUrl;
}

ResultVoid RadioRepository::persistFavorites() {
    nlohmann::json favorites = nlohmann::json::array();
    for (RadioEntity const& radio : m_favorites) {
        favorites.push_back(serializeRadio(radio));
    }

    return getContext().setString(Preferences::FAVORITES_KEY, favorites.dump());
}

ResultVoid RadioRepository::persistLastSelected() {
    if (!m_lastSelected.has_value()) {
        return getContext().remove(Preferences::LAST_SELECTED_KEY);
    }

    return getContext().setString(Preferences::LAST_SELECTED_KEY, serializeRadio(*m_lastSelected).dump());
}
