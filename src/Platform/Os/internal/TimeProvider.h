#ifndef QLOCKY_TIME_PROVIDER_H
#define QLOCKY_TIME_PROVIDER_H

#include "TimeProviderIfc.h"

class TimeProvider final : public TimeProviderIfc {
public:

    /**
     * @see TimeProviderIfc::getCurrentTimestamp
     */
    DateTime getCurrentTimestamp() const final;
};

#endif