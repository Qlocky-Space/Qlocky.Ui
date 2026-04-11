#ifndef QLOCKY_REST_API_MODULE_H
#define QLOCKY_REST_API_MODULE_H

#include "api/ModuleBase.h"

/**
 * Rest API module contains generic HTTP-based REST access.
 */
class RestApiModule final : public ModuleBase {
public:

    void registerExports(Injector& container) final;
    void registerQmlTypes() final;
    void onInitialize() final;

    RestApiModule() = default;
    ~RestApiModule() final = default;
};

#endif // QLOCKY_REST_API_MODULE_H