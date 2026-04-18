#ifndef SYSTEM_PREFERENCES_REPOSITORY_IFC_H
#define SYSTEM_PREFERENCES_REPOSITORY_IFC_H

#include <string>

/**
 * Represents an interface for an alarm setting repository.
 * This interface defines the basic operations for managing alarm settings.
 */
class SystemPreferencesRepositoryIfc {
public:

    virtual ~SystemPreferencesRepositoryIfc() = default;

    /**
     * Initializes the repository.
     * This method should be called to set up any necessary state or data structures.
     */
    virtual void initialize() = 0;

    /**
     * Gets the time format used for displaying time.
     * @return The time format as a string.
     */
    virtual std::string getTimeFormat() = 0;

    /**
     * Gets the time zone used for displaying time.
     * @return The time zone as a string.
     */
    virtual std::string getTimeZone() = 0;

    /**
     * Gets persisted display brightness in range 0..100.
     * @return Brightness percentage.
     */
    virtual uint8_t getDisplayBrightnessPercent() = 0;

    /**
     * Persists display brightness in range 0..100.
     * @param brightnessPercent Brightness percentage.
     */
    virtual void setDisplayBrightnessPercent(uint8_t brightnessPercent) = 0;

    /**
     * Gets persisted output volume in range 0..100.
     * @return Volume percentage.
     */
    virtual uint8_t getOutputVolumePercent() = 0;

    /**
     * Persists output volume in range 0..100.
     * @param volumePercent Volume percentage.
     */
    virtual void setOutputVolumePercent(uint8_t volumePercent) = 0;
};

#endif