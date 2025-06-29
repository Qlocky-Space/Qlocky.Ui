#include "QlockyApp.h"

#include <QCoreApplication>
#include <QQmlApplicationEngine>

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
    });

    engine.load(url);
}

void QlockyApp::finish() {
    m_modules.clear();
}
