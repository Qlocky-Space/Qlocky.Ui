#ifndef SRC_RADIO_INTERNAL_RADIO_PLAYER_H
#define SRC_RADIO_INTERNAL_RADIO_PLAYER_H

#include <Mediator.h>

#include "AudioOutputIfc.h"
#include "AudioOutputListenerIfc.h"
#include "RadioPlayerIfc.h"

/**
 * Default player implementation for radio playback commands.
 */
class RadioPlayer final : public RadioPlayerIfc, public AudioOutputListenerIfc {
public:

    /**
     * Create a radio player.
     * @param audioPlayer Audio player used for playback.
     * @param mediator Event mediator used to publish playback state changes.
     */
    RadioPlayer(AudioOutputIfc& audioPlayer, Mediator& mediator);

    /**
     * Destroy the player.
     */
    ~RadioPlayer() final;

    /**
     * @see RadioPlayerIfc::play
     */
    void play(RadioEntity const& radio) final;

    /**
     * @see RadioPlayerIfc::stop
     */
    void stop() final;

    /**
     * @see RadioPlayerIfc::isPlaying
     */
    bool isPlaying() const final;

    /**
     * @see AudioOutputListenerIfc::onPlaybackStarted
     */
    void onPlaybackStarted(std::string const& source) final;

    /**
     * @see AudioOutputListenerIfc::onPlaybackStopped
     */
    void onPlaybackStopped() final;

    /**
     * @see AudioOutputListenerIfc::onPlaybackFailed
     */
    void onPlaybackFailed(AudioOutputErrorCode errorCode) final;

private:

    void setPlaying(bool playing);

    AudioOutputIfc& m_audioPlayer;
    Mediator& m_mediator;
    bool m_playing {false};
};

#endif // SRC_RADIO_INTERNAL_RADIO_PLAYER_H
