#ifndef RADIO_SOURCE_VIEW_MODEL_BASE_H
#define RADIO_SOURCE_VIEW_MODEL_BASE_H

#include <Mediator.h>
#include <QObject>
#include <QString>
#include <QVariantList>
#include <Stream.h>
#include <unordered_set>
#include <vector>

#include "events/RadioFavoriteAddedEvent.h"
#include "events/RadioFavoriteRemovedEvent.h"
#include "events/RadioFavoriteUpdatedEvent.h"
#include "RadioSearchResult.h"
#include "RadioServiceIfc.h"

/**
 * Base view model providing shared radio source selection logic: search, favorites and
 * selection tracking without applying a global selection side effect.
 *
 * Subclasses can extend this to add context-specific confirmation behaviour
 * (e.g. choosing a station for playback vs. for an alarm).
 */
class RadioSourceViewModelBase : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QVariantList searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(QVariantList favorites READ favorites NOTIFY favoritesChanged)
    Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)
    Q_PROPERTY(bool searched READ searched NOTIFY searchedChanged)
    Q_PROPERTY(QString selectedSource READ selectedSource WRITE setSelectedSource NOTIFY selectedSourceChanged)

public:

    RadioSourceViewModelBase(Mediator& mediator, RadioServiceIfc& radioService);
    ~RadioSourceViewModelBase() override;

    /**
     * @return The current search text.
     */
    QString searchText() const {
        return m_searchText;
    }

    /**
     * @param searchText The new search text.
     */
    void setSearchText(QString const& searchText);

    /**
     * @return The current search results.
     */
    QVariantList searchResults() const {
        return m_searchResults;
    }

    /**
     * @return The user's favourite radios.
     */
    QVariantList favorites() const {
        return m_favorites;
    }

    /**
     * @return True while a search request is in progress.
     */
    bool searching() const {
        return m_searching;
    }

    /**
     * @return True after at least one search has been triggered.
     */
    bool searched() const {
        return m_searched;
    }

    /**
     * @return The currently highlighted radio source ID.
     */
    QString selectedSource() const {
        return m_selectedSource;
    }

    /**
     * @param selectedSource The ID of the source to highlight.
     */
    void setSelectedSource(QString const& selectedSource);

    /**
     * Resets search state and selection.
     */
    Q_INVOKABLE void resetSelection();

    /**
     * Starts a station search using the current search text.
     */
    Q_INVOKABLE void search();

    /**
     * Adds the given radio to favourites.
     * @param radioId The radio identifier.
     */
    Q_INVOKABLE void addFavorite(QString const& radioId);

    /**
     * Removes the given radio from favourites.
     * @param radioId The radio identifier.
     */
    Q_INVOKABLE void removeFavorite(QString const& radioId);

    /**
     * Toggles the favourite state for the given radio.
     * @param radioId The radio identifier.
     */
    Q_INVOKABLE void toggleFavorite(QString const& radioId);

signals:

    void searchTextChanged();
    void searchResultsChanged();
    void favoritesChanged();
    void searchingChanged();
    void searchedChanged();
    void selectedSourceChanged();

protected:

    /**
     * Looks up a radio entity by its ID in current search results and favourites.
     * @param radioId The radio identifier to look up.
     * @return The matching radio entity, or empty if not found.
     */
    [[nodiscard]] std::optional<RadioEntity> findRadioById(QString const& radioId) const;

    RadioServiceIfc& m_radioService;

private:

    void setSearchResults(QVariantList const& searchResults);
    void setFavorites(QVariantList const& favorites);
    void setSearching(bool searching);
    void setSearched(bool searched);
    void onSearchResult(RadioSearchResult const& result);
    void onSearchFinished();
    void onFavoriteAdded(RadioFavoriteAddedEvent const& event);
    void onFavoriteRemoved(RadioFavoriteRemovedEvent const& event);
    void onFavoriteUpdated(RadioFavoriteUpdatedEvent const& event);
    void refreshFavorites();
    void applySearchResults();
    [[nodiscard]] bool isFavorite(std::string const& radioId) const;

    QString m_searchText {};
    QVariantList m_searchResults {};
    QVariantList m_favorites {};
    bool m_searching {false};
    bool m_searched {false};
    QString m_selectedSource {};
    std::vector<RadioSearchResult> m_searchResultsData {};
    std::vector<RadioEntity> m_favoritesData {};
    std::unordered_set<std::string> m_favoriteIds {};
    Stream<RadioSearchResult>::Subscription m_searchSubscription {};
};

#endif
