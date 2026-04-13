#ifndef RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H
#define RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H

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

class RadioServiceIfc;

/**
 * ViewModel for the radio source selection dialog.
 */
class RadioSourceSelectDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QVariantList searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(QVariantList favorites READ favorites NOTIFY favoritesChanged)
    Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)
    Q_PROPERTY(bool searched READ searched NOTIFY searchedChanged)
    Q_PROPERTY(QString selectedSource READ selectedSource WRITE setSelectedSource NOTIFY selectedSourceChanged)

public:

    RadioSourceSelectDialogViewModel(Mediator& mediator, RadioServiceIfc& radioService);
    ~RadioSourceSelectDialogViewModel() final;

    /**
     * @return The search text.
     */
    QString searchText() const {
        return m_searchText;
    }

    /**
     * @param searchText The search text.
     */
    void setSearchText(QString const& searchText);

    /**
     * @return Search results.
     */
    QVariantList searchResults() const {
        return m_searchResults;
    }

    /**
     * @return Favorite radios.
     */
    QVariantList favorites() const {
        return m_favorites;
    }

    /**
     * @return Whether a search request is in progress.
     */
    bool searching() const {
        return m_searching;
    }

    /**
     * @return Whether at least one search was triggered.
     */
    bool searched() const {
        return m_searched;
    }

    /**
     * @return The currently selected radio source.
     */
    QString selectedSource() const {
        return m_selectedSource;
    }

    /**
     * @param selectedSource The currently selected radio source.
     */
    void setSelectedSource(QString const& selectedSource);

    /**
     * Resets the dialog to the default source.
     */
    Q_INVOKABLE void resetSelection();

    /**
     * Starts a station search using the current search text.
     */
    Q_INVOKABLE void search();

    /**
     * Selects the currently highlighted station.
     */
    Q_INVOKABLE void chooseSelectedStation();

    /**
     * Adds one radio to favorites.
     * @param radioId The radio identifier.
     */
    Q_INVOKABLE void addFavorite(QString const& radioId);

    /**
     * Removes one radio from favorites.
     * @param radioId The radio identifier.
     */
    Q_INVOKABLE void removeFavorite(QString const& radioId);

    /**
     * Toggles the favorite state for one radio.
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
    [[nodiscard]] std::optional<RadioEntity> findRadioById(QString const& radioId) const;

    RadioServiceIfc& m_radioService;
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
