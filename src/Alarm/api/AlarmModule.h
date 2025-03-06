#ifndef QLOCKY_ALARM_MODULE_H
#define QLOCKY_ALARM_MODULE_H

#include "api/ModuleIfc.h"

/**
 * Alarm module contains functionality for
 */
class AlarmModule : public ModuleIfc {
public:

    void registerExports(Injector& container) final;

    void registerQmlTypes() final;

private:
};

#endif