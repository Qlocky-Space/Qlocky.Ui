#ifndef DATE_TIME_PROVIDER_IFC_H
#define DATE_TIME_PROVIDER_IFC_H

#include <cinttypes>

/**
 * Interface to get the actual time and date of underlying OS
 */
class TimeServiceIfc {
public:

    /**
     * Gets the current unix timestamp
     * @return the unix timestamp
     */
    virtual uint64_t getCurrentTimestamp() const = 0;

    virtual ~TimeServiceIfc() = default;
};

#endif