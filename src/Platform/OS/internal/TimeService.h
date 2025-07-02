#ifndef QLOCKY_TIME_SERVICE_H
#define QLOCKY_TIME_SERVICE_H

#include "TimeServiceIfc.h"

class TimeService final : public TimeServiceIfc {
public:

    /**
     * @see TimeServiceIfc::getCurrentTimestamp
     */
    uint64_t getCurrentTimestamp() const final;

private:
};

#endif