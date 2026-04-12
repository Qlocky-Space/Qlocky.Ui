#include "RadioSourceSelectDialogViewModel.h"

#include <algorithm>
#include <ng-log/logging.h>
#include <QVariantMap>

#include "StationEntity.h"
#include "StationFilter.h"
#include "StationRepositoryIfc.h"
#include "StationServiceIfc.h"

namespace {

QVariantMap toSearchResult(StationEntity const& station) {
    QVariantMap result {};
    result.insert("id", QString::fromStdString(station.id.toString()));
    result.insert("name", QString::fromStdString(station.name));
    result.insert("votes", QVariant::fromValue(station.votes));
    result.insert("favicon", QString::fromStdString(station.favicon));
    result.insert("language", QString::fromStdString(station.language));
    return result;
}

} // namespace

RadioSourceSelectDialogViewModel::RadioSourceSelectDialogViewModel(
    StationServiceIfc& stationService,
    StationRepositoryIfc& stationRepository) :
    m_stationService {stationService},
    m_stationRepository {stationRepository} {
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
    m_searchStations.clear();
}

void RadioSourceSelectDialogViewModel::search() {
    if (m_searching) {
        return;
    }

    QString const trimmedSearchText {m_searchText.trimmed()};
    if (trimmedSearchText.isEmpty()) {
        m_searchSubscription.cancel();
        m_searchStations.clear();
        setSearchResults({});
        setSearching(false);
        setSearched(false);
        setSelectedSource({});
        return;
    }

    setSearching(true);
    setSearched(true);
    setSearchResults({});
    m_searchStations.clear();

    StationFilter filter {};
    filter.name = trimmedSearchText.toStdString();

    m_searchSubscription = m_stationService.searchStations(filter).consume(
        [this](StationEntity const& station) {
            onSearchStation(station);
        },
        [this]() {
            onSearchFinished();
        });
}

void RadioSourceSelectDialogViewModel::chooseSelectedStation() {
    auto const it = std::find_if(m_searchStations.begin(), m_searchStations.end(), [this](StationEntity const& station) {
        return QString::fromStdString(station.id.toString()) == m_selectedSource;
    });
    if (it == m_searchStations.end()) {
        return;
    }

    m_stationRepository.addStation(*it);
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

void RadioSourceSelectDialogViewModel::onSearchStation(StationEntity const& station) {
    m_searchStations.push_back(station);
}

void RadioSourceSelectDialogViewModel::onSearchFinished() {
    std::sort(m_searchStations.begin(), m_searchStations.end(), [](StationEntity const& lhs, StationEntity const& rhs) {
        if (lhs.votes == rhs.votes) {
            return lhs.name < rhs.name;
        }

        return lhs.votes > rhs.votes;
    });

    setSearching(false);
    applySearchResults();
}

void RadioSourceSelectDialogViewModel::applySearchResults() {
    QVariantList searchResults {};
    searchResults.reserve(static_cast<qsizetype>(m_searchStations.size()));
    for (StationEntity const& station : m_searchStations) {
        searchResults.push_back(toSearchResult(station));
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
