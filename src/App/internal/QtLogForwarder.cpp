#include "QtLogForwarder.h"

#include <ng-log/logging.h>

void QtLoggerForwarder::messageHandler(QtMsgType type, QMessageLogContext const& context, QString const& msg) {
    char const* file = context.file ? context.file : "";

    switch (type) {
        case QtDebugMsg:
            DLOG(INFO) << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
        case QtInfoMsg:
            LOG(INFO) << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
        case QtWarningMsg:
            LOG(WARNING) << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
        case QtCriticalMsg:
            LOG(ERROR) << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
        case QtFatalMsg:
            LOG(FATAL) << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
        default:
            LOG(ERROR) << "Unknown Qt message type: " << type << " " << file << ":" << context.line << " " << msg.toStdString();
            break;
    }
}
