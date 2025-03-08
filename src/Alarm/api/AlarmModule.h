#ifndef QLOCKY_ALARM_MODULE_H
#define QLOCKY_ALARM_MODULE_H

#include "api/ModuleBase.h"

/**
 * Alarm module contains functionality for
 */
class AlarmModule : public ModuleBase {
public:

    void registerExports(Injector& container) final;

    void registerQmlTypes() final;

private:
};

#endif