#ifndef DATE_TIME_PROVIDER_IFC_H
#define DATE_TIME_PROVIDER_IFC_H

#include <cinttypes>

using DateTime = uint64_t;

/**
 * Interface to get the actual time and date of underlying OS
 */
class TimeProviderIfc {
public:

    /**
     * Gets the current unix timestamp
     * @return the unix timestamp
     */
    virtual DateTime getCurrentTimestamp() const = 0;

    virtual ~TimeProviderIfc() = default;
};

#endif