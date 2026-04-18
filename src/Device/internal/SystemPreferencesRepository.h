#ifndef SYSTEM_PREFERENCES_REPOSITORY_H
#define SYSTEM_PREFERENCES_REPOSITORY_H

#include <cstdint>

#include "Mediator.h"
#include "PersistenceServiceIfc.h"
#include "SystemPreferencesRepositoryIfc.h"

/**
 * @see SystemPreferencesRepositoryIfc
 */
class SystemPreferencesRepository : public SystemPreferencesRepositoryIfc {
public:

    SystemPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency);

    /**
     * @see SystemPreferencesRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see SystemPreferencesRepositoryIfc::getTimeFormat
     */
    std::string getTimeFormat() final;

    /**
     * @see SystemPreferencesRepositoryIfc::getTimeZone
     */
    std::string getTimeZone() final;

    /**
     * @see SystemPreferencesRepositoryIfc::getDisplayBrightnessPercent
     */
    uint8_t getDisplayBrightnessPercent() final;

    /**
     * @see SystemPreferencesRepositoryIfc::setDisplayBrightnessPercent
     */
    void setDisplayBrightnessPercent(uint8_t brightnessPercent) final;

    /**
     * @see SystemPreferencesRepositoryIfc::getOutputVolumePercent
     */
    uint8_t getOutputVolumePercent() final;

    /**
     * @see SystemPreferencesRepositoryIfc::setOutputVolumePercent
     */
    void setOutputVolumePercent(uint8_t volumePercent) final;

private:

    static std::string const SYSTEM_PREFERENCES_NAMESPACE;

    struct Preferences final {
        inline static std::string const PROP_TIMEZONE_KEY {"TimeZone"};
        inline static std::string const PROP_24H_FORMAT_KEY {"24HFormat"};
        inline static std::string const PROP_DISPLAY_BRIGHTNESS_PERCENT_KEY {"DisplayBrightnessPercent"};
        inline static std::string const PROP_OUTPUT_VOLUME_PERCENT_KEY {"OutputVolumePercent"};
    };

    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(SYSTEM_PREFERENCES_NAMESPACE);
    }

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
};

#endif