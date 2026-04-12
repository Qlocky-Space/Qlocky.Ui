#include "RadioCardViewModel.h"

RadioCardViewModel::RadioCardViewModel(Mediator& mediator, RadioServiceIfc& radioService, RadioPlayerIfc& radioController) :
    QObject {nullptr},
    m_radioService {radioService},
    m_radioController {radioController} {
    applyRadio(radioService.selectedRadio());
    setPlaying(radioController.isPlaying());

    mediator.subscribe<RadioSelectionChangedEvent>(this, &RadioCardViewModel::onSelectionChanged);
    mediator.subscribe<RadioPlaybackStateChangedEvent>(this, &RadioCardViewModel::onPlaybackStateChanged);
}

void RadioCardViewModel::togglePlayback() {
    if (m_radioController.isPlaying()) {
        m_radioController.stop();
        return;
    }

    auto const selectedRadio = m_radioService.selectedRadio();
    if (!selectedRadio.has_value()) {
        return;
    }

    m_radioController.play(*selectedRadio);
}

void RadioCardViewModel::setTitle(QString const& title) {
    if (m_title == title) {
        return;
    }

    m_title = title;
    emit titleChanged();
}

void RadioCardViewModel::setSubtitle(QString const& subtitle) {
    if (m_subtitle == subtitle) {
        return;
    }

    m_subtitle = subtitle;
    emit subtitleChanged();
}

void RadioCardViewModel::setPlaying(bool playing) {
    if (m_playing == playing) {
        return;
    }

    m_playing = playing;
    emit playingChanged();
}

void RadioCardViewModel::setHasRadio(bool hasRadio) {
    if (m_hasRadio == hasRadio) {
        return;
    }

    m_hasRadio = hasRadio;
    emit hasRadioChanged();
}

void RadioCardViewModel::applyRadio(std::optional<RadioEntity> const& radio) {
    if (!radio.has_value()) {
        setTitle("No Radio Selected");
        setSubtitle("Choose a source");
        setHasRadio(false);
        return;
    }

    setTitle(QString::fromStdString(radio->name));
    setSubtitle(QString::fromStdString(radio->provider));
    setHasRadio(true);
}

void RadioCardViewModel::onSelectionChanged(RadioSelectionChangedEvent const& event) {
    applyRadio(event.radio);
}

void RadioCardViewModel::onPlaybackStateChanged(RadioPlaybackStateChangedEvent const& event) {
    setPlaying(event.playing);
}
