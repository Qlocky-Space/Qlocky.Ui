#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QProcessEnvironment>
#include <QScreen>

int main(int argc, char *argv[])
{
    qInfo("Qlocky 3 App started");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []()
                     { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.load("qrc:/qt/qml/QlockyModule/src/mainwindow.qml");

    return app.exec();
}
