#include "RadioCardViewModel.h"

RadioCardViewModel::RadioCardViewModel(Mediator& mediator, RadioServiceIfc& radioService, RadioPlayerIfc& radioController) :
    QObject {nullptr},
    m_radioService {radioService},
    m_radioController {radioController} {
    applyRadio(radioService.selectedRadio());
    setPlaying(radioController.isPlaying());

    mediator.subscribe<RadioSelectionChangedEvent>(this, &RadioCardViewModel::onSelectionChanged);
    mediator.subscribe<RadioPlaybackStateChangedEvent>(this, &RadioCardViewModel::onPlaybackStateChanged);
    mediator.subscribe<RadioFavoriteAddedEvent>(this, &RadioCardViewModel::onFavoriteAdded);
    mediator.subscribe<RadioFavoriteRemovedEvent>(this, &RadioCardViewModel::onFavoriteRemoved);
    mediator.subscribe<RadioFavoriteUpdatedEvent>(this, &RadioCardViewModel::onFavoriteUpdated);
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

void RadioCardViewModel::toggleFavorite() {
    auto const selectedRadio = m_radioService.selectedRadio();
    if (!selectedRadio.has_value()) {
        return;
    }

    if (m_favorite) {
        m_radioService.removeFavorite(selectedRadio->id);
        return;
    }

    m_radioService.addFavorite(*selectedRadio);
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

void RadioCardViewModel::setIconUrl(QString const& iconUrl) {
    if (m_iconUrl == iconUrl) {
        return;
    }

    m_iconUrl = iconUrl;
    emit iconUrlChanged();
}

void RadioCardViewModel::setPlaying(bool playing) {
    if (m_playing == playing) {
        return;
    }

    m_playing = playing;
    emit playingChanged();
}

void RadioCardViewModel::setFavorite(bool favorite) {
    if (m_favorite == favorite) {
        return;
    }

    m_favorite = favorite;
    emit favoriteChanged();
}

void RadioCardViewModel::setHasSelection(bool hasSelection) {
    if (m_hasSelection == hasSelection) {
        return;
    }

    m_hasSelection = hasSelection;
    emit hasSelectionChanged();
}

void RadioCardViewModel::setIsControllable(bool isControllable) {
    if (m_isControllable == isControllable) {
        return;
    }

    m_isControllable = isControllable;
    emit isControllableChanged();
}

void RadioCardViewModel::refreshFavoriteState() {
    auto const selectedRadio = m_radioService.selectedRadio();
    if (!selectedRadio.has_value()) {
        setFavorite(false);
        return;
    }

    auto const favorites = m_radioService.favorites();
    auto const favoriteIt = std::find_if(favorites.begin(), favorites.end(), [&selectedRadio](RadioEntity const& radio) {
        return radio.id == selectedRadio->id;
    });
    setFavorite(favoriteIt != favorites.end());
}

void RadioCardViewModel::applyRadio(std::optional<RadioEntity> const& radio) {
    if (!radio.has_value()) {
        setTitle("No Radio Selected");
        setSubtitle("Choose a source");
        setIconUrl({});
        setFavorite(false);
        setHasSelection(false);
        setIsControllable(false);
        return;
    }

    setTitle(QString::fromStdString(radio->name));
    setSubtitle(QString::fromStdString(radio->provider));
    setIconUrl(QString::fromStdString(radio->iconUrl));
    setHasSelection(true);
    setIsControllable(false);
    refreshFavoriteState();
}

void RadioCardViewModel::onSelectionChanged(RadioSelectionChangedEvent const& event) {
    applyRadio(event.radio);

    // if radio is already playing, start playback for the new selection
    if (m_playing && event.radio.has_value()) {
        m_radioController.stop();
        m_radioController.play(event.radio.value());
    }
}

void RadioCardViewModel::onPlaybackStateChanged(RadioPlaybackStateChangedEvent const& event) {
    setPlaying(event.playing);
}

void RadioCardViewModel::onFavoriteAdded(RadioFavoriteAddedEvent const& event) {
    Q_UNUSED(event);
    refreshFavoriteState();
}

void RadioCardViewModel::onFavoriteRemoved(RadioFavoriteRemovedEvent const& event) {
    Q_UNUSED(event);
    refreshFavoriteState();
}

void RadioCardViewModel::onFavoriteUpdated(RadioFavoriteUpdatedEvent const& event) {
    Q_UNUSED(event);
    refreshFavoriteState();
}
