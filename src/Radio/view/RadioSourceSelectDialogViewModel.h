#ifndef RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H
#define RADIO_SOURCE_SELECT_DIALOG_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <Stream.h>

#include "RadioSearchResult.h"

class RadioServiceIfc;

/**
 * ViewModel for the radio source selection dialog.
 */
class RadioSourceSelectDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString searchText READ searchText WRITE setSearchText NOTIFY searchTextChanged)
    Q_PROPERTY(QVariantList searchResults READ searchResults NOTIFY searchResultsChanged)
    Q_PROPERTY(bool searching READ searching NOTIFY searchingChanged)
    Q_PROPERTY(bool searched READ searched NOTIFY searchedChanged)
    Q_PROPERTY(QString selectedSource READ selectedSource WRITE setSelectedSource NOTIFY selectedSourceChanged)

public:

    RadioSourceSelectDialogViewModel(RadioServiceIfc& radioService);
    ~RadioSourceSelectDialogViewModel() final = default;

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
     * Adds the currently selected station to the favorites repository.
     */
    Q_INVOKABLE void chooseSelectedStation();

signals:

    void searchTextChanged();
    void searchResultsChanged();
    void searchingChanged();
    void searchedChanged();
    void selectedSourceChanged();

private:

    void setSearchResults(QVariantList const& searchResults);
    void setSearching(bool searching);
    void setSearched(bool searched);
    void onSearchResult(RadioSearchResult const& result);
    void onSearchFinished();
    void applySearchResults();

    RadioServiceIfc& m_radioService;
    QString m_searchText {};
    QVariantList m_searchResults {};
    bool m_searching {false};
    bool m_searched {false};
    QString m_selectedSource {};
    std::vector<RadioSearchResult> m_searchResultsData {};
    Stream<RadioSearchResult>::Subscription m_searchSubscription {};
};

#endif
