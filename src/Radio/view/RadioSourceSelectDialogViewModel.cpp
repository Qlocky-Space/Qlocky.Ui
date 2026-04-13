#include "RadioSourceSelectDialogViewModel.h"

#include <algorithm>
#include <optional>
#include <QVariantMap>

#include "RadioSearchFilter.h"
#include "RadioServiceIfc.h"

namespace {

QVariantMap toFavoriteResult(RadioEntity const& radio) {
    QVariantMap resultMap {};
    resultMap.insert("id", QString::fromStdString(radio.id));
    resultMap.insert("name", QString::fromStdString(radio.name));
    resultMap.insert("provider", QString::fromStdString(radio.provider));
    resultMap.insert("favicon", QString::fromStdString(radio.iconUrl));
    return resultMap;
}

QVariantMap toSearchResult(RadioSearchResult const& searchResult, bool favorite) {
    QVariantMap resultMap {};
    resultMap.insert("id", QString::fromStdString(searchResult.radio.id));
    resultMap.insert("name", QString::fromStdString(searchResult.radio.name));
    resultMap.insert("votes", QVariant::fromValue(searchResult.votes));
    resultMap.insert("favicon", QString::fromStdString(searchResult.favicon));
    resultMap.insert("language", QString::fromStdString(searchResult.language));
    resultMap.insert("isFavorite", favorite);
    return resultMap;
}

} // namespace

RadioSourceSelectDialogViewModel::RadioSourceSelectDialogViewModel(Mediator& mediator, RadioServiceIfc& radioService) :
    m_radioService {radioService} {
    refreshFavorites();
    mediator.subscribe<RadioFavoriteAddedEvent>(this, &RadioSourceSelectDialogViewModel::onFavoriteAdded);
    mediator.subscribe<RadioFavoriteRemovedEvent>(this, &RadioSourceSelectDialogViewModel::onFavoriteRemoved);
    mediator.subscribe<RadioFavoriteUpdatedEvent>(this, &RadioSourceSelectDialogViewModel::onFavoriteUpdated);
}

RadioSourceSelectDialogViewModel::~RadioSourceSelectDialogViewModel() {
    m_searchSubscription.cancel();
}

void RadioSourceSelectDialogViewModel::setSearchText(QString const& searchText) {
    if (m_searchText == searchText) {
        return;
    }

    m_searchText = searchText;
    emit searchTextChanged();
}

void RadioSourceSelectDialogViewModel::setSelectedSource(QString const& selectedSource) {
    if (m_selectedSource == selectedSource) {
        return;
    }

    m_selectedSource = selectedSource;
    emit selectedSourceChanged();
}

void RadioSourceSelectDialogViewModel::resetSelection() {
    m_searchSubscription.cancel();
    setSearchText({});
    setSearchResults({});
    setSearching(false);
    setSearched(false);
    setSelectedSource({});
    m_searchResultsData.clear();
    refreshFavorites();
}

void RadioSourceSelectDialogViewModel::search() {
    if (m_searching) {
        return;
    }

    QString const trimmedSearchText {m_searchText.trimmed()};
    if (trimmedSearchText.isEmpty()) {
        m_searchSubscription.cancel();
        m_searchResultsData.clear();
        setSearchResults({});
        setSearching(false);
        setSearched(false);
        setSelectedSource({});
        return;
    }

    setSearching(true);
    setSearched(true);
    setSearchResults({});
    m_searchResultsData.clear();

    RadioSearchFilter filter {};
    filter.name = trimmedSearchText.toStdString();

    m_searchSubscription = m_radioService.searchRadios(filter).consume([this](RadioSearchResult const& result) { onSearchResult(result); }, [this]() { onSearchFinished(); });
}

void RadioSourceSelectDialogViewModel::chooseSelectedStation() {
    auto const radio = findRadioById(m_selectedSource);
    if (!radio.has_value()) {
        return;
    }

    m_radioService.selectRadio(*radio);
}

void RadioSourceSelectDialogViewModel::addFavorite(QString const& radioId) {
    auto const radio = findRadioById(radioId);
    if (!radio.has_value()) {
        return;
    }

    m_radioService.addFavorite(*radio);
}

void RadioSourceSelectDialogViewModel::removeFavorite(QString const& radioId) {
    if (radioId.isEmpty()) {
        return;
    }

    m_radioService.removeFavorite(radioId.toStdString());
}

void RadioSourceSelectDialogViewModel::toggleFavorite(QString const& radioId) {
    if (radioId.isEmpty()) {
        return;
    }

    if (isFavorite(radioId.toStdString())) {
        removeFavorite(radioId);
        return;
    }

    addFavorite(radioId);
}

void RadioSourceSelectDialogViewModel::setSearchResults(QVariantList const& searchResults) {
    if (m_searchResults == searchResults) {
        return;
    }

    m_searchResults = searchResults;
    emit searchResultsChanged();
}

void RadioSourceSelectDialogViewModel::setFavorites(QVariantList const& favorites) {
    if (m_favorites == favorites) {
        return;
    }

    m_favorites = favorites;
    emit favoritesChanged();
}

void RadioSourceSelectDialogViewModel::setSearching(bool searching) {
    if (m_searching == searching) {
        return;
    }

    m_searching = searching;
    emit searchingChanged();
}

void RadioSourceSelectDialogViewModel::setSearched(bool searched) {
    if (m_searched == searched) {
        return;
    }

    m_searched = searched;
    emit searchedChanged();
}

void RadioSourceSelectDialogViewModel::onSearchResult(RadioSearchResult const& result) {
    m_searchResultsData.push_back(result);
}

void RadioSourceSelectDialogViewModel::onSearchFinished() {
    setSearching(false);
    applySearchResults();
}

void RadioSourceSelectDialogViewModel::onFavoriteAdded(RadioFavoriteAddedEvent const& event) {
    Q_UNUSED(event);
    refreshFavorites();
    applySearchResults();
}

void RadioSourceSelectDialogViewModel::onFavoriteRemoved(RadioFavoriteRemovedEvent const& event) {
    Q_UNUSED(event);
    refreshFavorites();
    applySearchResults();
}

void RadioSourceSelectDialogViewModel::onFavoriteUpdated(RadioFavoriteUpdatedEvent const& event) {
    Q_UNUSED(event);
    refreshFavorites();
    applySearchResults();
}

void RadioSourceSelectDialogViewModel::refreshFavorites() {
    m_favoritesData = m_radioService.favorites();
    m_favoriteIds.clear();

    QVariantList favorites {};
    favorites.reserve(static_cast<qsizetype>(m_favoritesData.size()));
    for (RadioEntity const& radio : m_favoritesData) {
        m_favoriteIds.insert(radio.id);
        favorites.push_back(toFavoriteResult(radio));
    }

    setFavorites(favorites);
}

void RadioSourceSelectDialogViewModel::applySearchResults() {
    QVariantList searchResults {};
    searchResults.reserve(static_cast<qsizetype>(m_searchResultsData.size()));
    for (RadioSearchResult const& result : m_searchResultsData) {
        searchResults.push_back(toSearchResult(result, isFavorite(result.radio.id)));
    }

    setSearchResults(searchResults);

    for (QVariant const& stationVariant : searchResults) {
        QVariantMap const station {stationVariant.toMap()};
        if (station.value("id").toString() == m_selectedSource) {
            return;
        }
    }

    for (QVariant const& stationVariant : m_favorites) {
        QVariantMap const station {stationVariant.toMap()};
        if (station.value("id").toString() == m_selectedSource) {
            return;
        }
    }

    if (searchResults.isEmpty() && m_favorites.isEmpty()) {
        setSelectedSource({});
        return;
    }

    if (!searchResults.isEmpty()) {
        setSelectedSource(searchResults.first().toMap().value("id").toString());
    }
}

bool RadioSourceSelectDialogViewModel::isFavorite(std::string const& radioId) const {
    return m_favoriteIds.find(radioId) != m_favoriteIds.end();
}

std::optional<RadioEntity> RadioSourceSelectDialogViewModel::findRadioById(QString const& radioId) const {
    if (radioId.isEmpty()) {
        return std::nullopt;
    }

    auto const searchIt = std::find_if(m_searchResultsData.begin(), m_searchResultsData.end(), [&radioId](RadioSearchResult const& result) {
        return QString::fromStdString(result.radio.id) == radioId;
    });
    if (searchIt != m_searchResultsData.end()) {
        return searchIt->radio;
    }

    auto const favoriteIt = std::find_if(m_favoritesData.begin(), m_favoritesData.end(), [&radioId](RadioEntity const& radio) {
        return QString::fromStdString(radio.id) == radioId;
    });
    if (favoriteIt != m_favoritesData.end()) {
        return *favoriteIt;
    }

    return std::nullopt;
}
