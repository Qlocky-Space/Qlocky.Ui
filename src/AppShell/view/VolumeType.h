#ifndef VOLUME_TYPE_H
#define VOLUME_TYPE_H

#include <QObject>

/**
 * VolumeType is an enumeration representing the different types of volume settings.
 */
class VolumeType : public QObject {
    Q_OBJECT

public:

    enum class Level {
        Mute,
        Vibration,
        Acoustic
    };
    Q_ENUM(Level)
};

#endif