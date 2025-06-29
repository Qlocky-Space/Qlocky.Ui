#ifndef QLOCKY_WEATHER_MODULE_H
#define QLOCKY_WEATHER_MODULE_H

#include "api/ModuleBase.h"

/**
 * Weather module contains functionality for
 */
class WeatherModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;

    WeatherModule() = default;
    ~WeatherModule() final = default;

private:
};

#endif