#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H

#include <ng-log/logging.h>

#include "PersistenceServiceIfc.h"

/**
 * ConsoleSink is a custom log sink that outputs log messages to the console.
 * It implements the nglog::LogSink interface and provides a method to send log messages.
 * This class is used to log messages in a format suitable for console output.
 */
class ConsoleSink : public nglog::LogSink {
public:

    /**
     * @see nglog::LogSink::send
     */
    void send(nglog::LogSeverity severity,
        char const* full_filename,
        char const* base_filename,
        int line,
        nglog::LogMessageTime const& time,
        char const* message,
        std::size_t message_len) final;
};

#endif