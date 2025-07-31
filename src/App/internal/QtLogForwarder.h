#ifndef QT_LOGGER_FORWARDER_H
#define QT_LOGGER_FORWARDER_H

#include <QMessageLogContext>
#include <QString>

/**
 * QtLoggerForwarder is a utility class that forwards Qt log messages to the nglog logging system.
 */
class QtLoggerForwarder {
public:

    /**
     * Installs the Qt message handler to forward log messages to nglog.
     */
    static void install() {
        // Install the message handler to forward Qt log messages
        qInstallMessageHandler(QtLoggerForwarder::messageHandler);
    }

    /**
     * Handles Qt log messages and forwards them to the nglog logging system.
     * @param type The type of the log message (debug, info, warning, critical, fatal).
     * @param context The context of the log message, including file name, line number, function name, and category.
     * @param msg The log message to be forwarded.
     */
    static void messageHandler(QtMsgType type, QMessageLogContext const& context, QString const& msg);

    QtLoggerForwarder() = delete;
    QtLoggerForwarder(QtLoggerForwarder const&) = delete;
    QtLoggerForwarder& operator=(QtLoggerForwarder const&) = delete;
    QtLoggerForwarder(QtLoggerForwarder&&) = delete;
    QtLoggerForwarder& operator=(QtLoggerForwarder&&) = delete;
};

#endif