#ifndef QLOCKY_ALARM_MODULE_H
#define QLOCKY_ALARM_MODULE_H

#include "api/ModuleBase.h"

/**
 * Alarm module contains functionality for
 */
class AlarmModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    /**
     * @see ModuleBase::registerQmlTypes
     */
    void registerQmlTypes() final;

    AlarmModule() = default;
    ~AlarmModule() final = default;

private:
};

#endif