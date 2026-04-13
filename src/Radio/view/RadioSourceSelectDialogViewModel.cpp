#include "RadioSourceSelectDialogViewModel.h"

#include <algorithm>
#include <QVariantMap>

#include "RadioSearchFilter.h"
#include "RadioServiceIfc.h"

namespace {

QVariantMap toSearchResult(RadioSearchResult const& searchResult) {
    QVariantMap resultMap {};
    resultMap.insert("id", QString::fromStdString(searchResult.radio.id));
    resultMap.insert("name", QString::fromStdString(searchResult.radio.name));
    resultMap.insert("votes", QVariant::fromValue(searchResult.votes));
    resultMap.insert("favicon", QString::fromStdString(searchResult.favicon));
    resultMap.insert("language", QString::fromStdString(searchResult.language));
    return resultMap;
}

} // namespace

RadioSourceSelectDialogViewModel::RadioSourceSelectDialogViewModel(RadioServiceIfc& radioService) :
    m_radioService {radioService} {
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
    auto const it = std::find_if(m_searchResultsData.begin(), m_searchResultsData.end(), [this](RadioSearchResult const& result) {
        return QString::fromStdString(result.radio.id) == m_selectedSource;
    });
    if (it == m_searchResultsData.end()) {
        return;
    }

    m_radioService.addFavorite(it->radio);
    m_radioService.selectRadio(it->radio);
}

void RadioSourceSelectDialogViewModel::setSearchResults(QVariantList const& searchResults) {
    if (m_searchResults == searchResults) {
        return;
    }

    m_searchResults = searchResults;
    emit searchResultsChanged();
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

void RadioSourceSelectDialogViewModel::applySearchResults() {
    QVariantList searchResults {};
    searchResults.reserve(static_cast<qsizetype>(m_searchResultsData.size()));
    for (RadioSearchResult const& result : m_searchResultsData) {
        searchResults.push_back(toSearchResult(result));
    }

    setSearchResults(searchResults);

    for (QVariant const& stationVariant : searchResults) {
        QVariantMap const station {stationVariant.toMap()};
        if (station.value("id").toString() == m_selectedSource) {
            return;
        }
    }

    if (searchResults.isEmpty()) {
        setSelectedSource({});
        return;
    }

    setSelectedSource(searchResults.first().toMap().value("id").toString());
}
