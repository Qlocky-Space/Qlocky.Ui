#ifndef SRC_RADIO_INTERNAL_RADIO_REPOSITORY_H
#define SRC_RADIO_INTERNAL_RADIO_REPOSITORY_H

#include <Mediator.h>
#include <optional>
#include <PersistenceServiceIfc.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "RadioRepositoryIfc.h"

class RadioRepository final : public RadioRepositoryIfc {
public:

    RadioRepository(Mediator& mediator, PersistenceServiceIfc& persistency);
    ~RadioRepository() final = default;

    void initialize() final;
    void addFavorite(RadioEntity const& radio) final;
    void removeFavorite(RadioId const& radioId) final;
    std::optional<RadioEntity> getFavorite(RadioId const& radioId) const final;
    std::vector<RadioEntity> getFavorites() const final {
        return m_favorites;
    }
    void setLastSelected(std::optional<RadioEntity> const& radio) final;
    std::optional<RadioEntity> getLastSelected() const final {
        return m_lastSelected;
    }

private:

    static std::string const RADIO_NAMESPACE;

    struct Preferences final {
        inline static std::string const FAVORITES_KEY {"Favorites"};
        inline static std::string const LAST_SELECTED_KEY {"LastSelected"};
    };

    static constexpr std::size_t INITIAL_CAPACITY {128};

    static bool areEqual(RadioEntity const& lhs, RadioEntity const& rhs);
    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(RADIO_NAMESPACE);
    }
    ResultVoid persistFavorites();
    ResultVoid persistLastSelected();

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
    std::vector<RadioEntity> m_favorites {};
    std::unordered_map<RadioId, std::size_t> m_favoriteIndexById {};
    std::optional<RadioEntity> m_lastSelected {};
};

#endif // SRC_RADIO_INTERNAL_RADIO_REPOSITORY_H
