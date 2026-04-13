#ifndef SRC_RADIO_API_RADIO_PLAYER_IFC_H
#define SRC_RADIO_API_RADIO_PLAYER_IFC_H

#include "RadioEntity.h"

/**
 * Plays and stops one passed radio entity.
 */
class RadioPlayerIfc {
public:

    virtual ~RadioPlayerIfc() = default;

    /**
     * Initialize the player. Must be called before any other method.
     */
    virtual void initialize() = 0;

    /**
     * Start playback for the given radio entity.
     * @param radio The radio to play.
     */
    virtual void play(RadioEntity const& radio) = 0;

    /**
     * Stop playback.
     */
    virtual void stop() = 0;

    /**
     * @return True when playback is active.
     */
    virtual bool isPlaying() const = 0;
};

#endif // SRC_RADIO_API_RADIO_PLAYER_IFC_H
