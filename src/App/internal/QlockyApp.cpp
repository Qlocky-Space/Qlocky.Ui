#include "QlockyApp.h"

#include <QCoreApplication>
#include <QMetaObject>
#include <QQmlApplicationEngine>

#include "UiEngineIfc.h"

QlockyApp::QlockyApp() :
    m_container {} {
}

void QlockyApp::addModule(std::unique_ptr<ModuleBase> module) {
    m_modules.push_back(std::move(module));
}

void QlockyApp::perform(Injector& container) {
    m_container = &container;

    for (std::unique_ptr<ModuleBase>& module : m_modules) {
        module->initialize(container);
    }

    auto& engine {resolve<UiEngineIfc>()->getAppEngine()};

    // QMetaObject::invokeMethod(qApp, [this]() {
    //     // for (ModuleSetupIfc* module : m_modules) {
    //     //     module->onStartApp();
    //     // }
    // },Qt::QueuedConnection);

    QUrl const url("qrc:/qt/qml/AppShell/qml/AppWindow.qml");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, qApp, [this, url](QObject* obj, QUrl const& objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
            return;
        }
    });

    engine.load(url);
}

void QlockyApp::finish() {
    // for (ModuleSetupIfc* module : m_modules) {
    //     module->onDeinit();
    // }

    // for (ModuleSetupIfc* module : m_modules) {
    //     module->onDestroy();
    // }

    // TODO remove IOC
    m_modules.clear();
}
