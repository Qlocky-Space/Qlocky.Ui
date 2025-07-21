#include "QlockyApp.h"

#include <events/ApplicationClosedEvent.h>
#include <events/ApplicationStartedEvent.h>
#include <Mediator.h>
#include <QCoreApplication>
#include <QQmlApplicationEngine>

#include "Navigation/InteractiveNavigatorIfc.h"
#include "UiEngineIfc.h"

void QlockyApp::addModule(std::unique_ptr<ModuleBase> module) {
    m_modules.push_back(std::move(module));
}

void QlockyApp::start(Injector& container) {
    m_container = &container;

    // Registers all modules
    for (std::unique_ptr<ModuleBase>& module : m_modules) {
        module->registers(container);
    }

    for (std::unique_ptr<ModuleBase>& module : m_modules) {
        module->initialize();
    }

    QUrl const url("qrc:/qt/qml/AppShell/qml/Main.qml");
    auto& engine {resolve<UiEngineIfc>()->getAppEngine()};
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, qApp, [this, url](QObject* obj, QUrl const& objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
            return;
        }

        auto navigator = resolve<InteractiveNavigatorIfc>();
        navigator->navigateTo(UriQuery {"qlocky://main"});

        auto mediator = resolve<Mediator>();
        mediator->notify(ApplicationStartedEvent {});
    });

    QObject::connect(&engine, &QQmlApplicationEngine::exit, qApp, [this](int code) {
        QCoreApplication::quit();
    });

    engine.load(url);
}

void QlockyApp::finish() {
    auto mediator = resolve<Mediator>();
    mediator->notify(ApplicationClosedEvent {});

    m_modules.clear();
}
