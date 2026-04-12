#ifndef SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H
#define SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H

#include <Mediator.h>
#include <optional>
#include <QObject>
#include <QString>

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
    Q_PROPERTY(bool playing READ playing NOTIFY playingChanged)
    Q_PROPERTY(bool hasRadio READ hasRadio NOTIFY hasRadioChanged)

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

    bool playing() const {
        return m_playing;
    }

    bool hasRadio() const {
        return m_hasRadio;
    }

    /**
     * Toggle playback for the currently selected radio.
     */
    Q_INVOKABLE void togglePlayback();

signals:

    void titleChanged();
    void subtitleChanged();
    void playingChanged();
    void hasRadioChanged();

private:

    void setTitle(QString const& title);
    void setSubtitle(QString const& subtitle);
    void setPlaying(bool playing);
    void setHasRadio(bool hasRadio);
    void applyRadio(std::optional<RadioEntity> const& radio);
    void onSelectionChanged(RadioSelectionChangedEvent const& event);
    void onPlaybackStateChanged(RadioPlaybackStateChangedEvent const& event);

    RadioServiceIfc& m_radioService;
    RadioPlayerIfc& m_radioController;
    QString m_title {"No Radio Selected"};
    QString m_subtitle {"Choose a source"};
    bool m_playing {false};
    bool m_hasRadio {false};
};

#endif // SRC_RADIO_VIEW_RADIO_CARD_VIEW_MODEL_H
