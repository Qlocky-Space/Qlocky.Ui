#ifndef SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H
#define SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H

#include <Mediator.h>
#include <optional>
#include <QObject>
#include <QString>

#include "events/RadioFavoriteAddedEvent.h"
#include "events/RadioFavoriteRemovedEvent.h"
#include "events/RadioFavoriteUpdatedEvent.h"
#include "events/RadioPlaybackStateChangedEvent.h"
#include "events/RadioSelectionChangedEvent.h"
#include "RadioPlayerIfc.h"
#include "RadioServiceIfc.h"

/**
 * View model for the radio card widget.
 */
class RadioCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString subtitle READ subtitle NOTIFY subtitleChanged)
    Q_PROPERTY(QString iconUrl READ iconUrl NOTIFY iconUrlChanged)
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(bool favorite READ favorite NOTIFY favoriteChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY hasSelectionChanged)
    Q_PROPERTY(bool isControllable READ isControllable NOTIFY isControllableChanged)

public:

    /**
     * Create the radio card view model.
     * @param mediator Event mediator used for radio updates.
     * @param radioService Radio service used for selected radio state.
     * @param radioController Player used for playback commands.
     */
    RadioCardViewModel(Mediator& mediator, RadioServiceIfc& radioService, RadioPlayerIfc& radioController);
    ~RadioCardViewModel() final = default;

    QString title() const {
        return m_title;
    }

    QString subtitle() const {
        return m_subtitle;
    }

    QString iconUrl() const {
        return m_iconUrl;
    }

    bool playing() const {
        return m_playing;
    }

    bool favorite() const {
        return m_favorite;
    }

    bool hasSelection() const {
        return m_hasSelection;
    }

    bool isControllable() const {
        return m_isControllable;
    }

    /**
     * Toggle playback for the currently selected radio.
     */
    Q_INVOKABLE void togglePlayback();

    /**
     * Toggle the favorite state for the currently selected radio.
     */
    Q_INVOKABLE void toggleFavorite();

signals:

    void titleChanged();
    void subtitleChanged();
    void iconUrlChanged();
    void playingChanged();
    void favoriteChanged();
    void hasSelectionChanged();
    void isControllableChanged();

private:

    void setTitle(QString const& title);
    void setSubtitle(QString const& subtitle);
    void setIconUrl(QString const& iconUrl);
    void setPlaying(bool playing);
    void setFavorite(bool favorite);
    void setHasSelection(bool hasSelection);
    void setIsControllable(bool isControllable);
    void refreshFavoriteState();
    void applyRadio(std::optional<RadioEntity> const& radio);
    void onSelectionChanged(RadioSelectionChangedEvent const& event);
    void onPlaybackStateChanged(RadioPlaybackStateChangedEvent const& event);
    void onFavoriteAdded(RadioFavoriteAddedEvent const& event);
    void onFavoriteRemoved(RadioFavoriteRemovedEvent const& event);
    void onFavoriteUpdated(RadioFavoriteUpdatedEvent const& event);

    RadioServiceIfc& m_radioService;
    RadioPlayerIfc& m_radioController;
    QString m_title {"No Radio Selected"};
    QString m_subtitle {"Choose a source"};
    QString m_iconUrl {};
    bool m_playing {false};
    bool m_favorite {false};
    bool m_hasSelection {false};
    bool m_isControllable {false};
};

#endif // SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H
