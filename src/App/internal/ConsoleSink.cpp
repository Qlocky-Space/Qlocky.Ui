#include "ConsoleSink.h"

#include <algorithm>
#include <iostream>

namespace {

void changeColor(nglog::LogSeverity severity) {
    switch (severity) {
        case nglog::LogSeverity::NGLOG_INFO:
            std::cout << "\033[32m"; // Green
            break;
        case nglog::LogSeverity::NGLOG_WARNING:
            std::cout << "\033[33m"; // Yellow
            break;
        case nglog::LogSeverity::NGLOG_ERROR:
            std::cout << "\033[31m"; // Red
            break;
        case nglog::LogSeverity::NGLOG_FATAL:
            std::cout << "\033[35m"; // Magenta
            break;
        default:
            std::cout << "\033[0m"; // Reset
    }
}

void resetColor() {
    std::cout << "\033[0m"; // Reset color
}

} // namespace

void ConsoleSink::send(nglog::LogSeverity severity,
    char const* full_filename,
    char const* base_filename,
    int line,
    nglog::LogMessageTime const& time,
    char const* message,
    std::size_t message_len) {
    // Forward the log message to the console
    changeColor(severity);
    std::cout << "[" << nglog::GetLogSeverityName(severity) << " - " << base_filename << ":" << line << "] ";
    std::copy_n(message, message_len, std::ostreambuf_iterator<char> {std::cout});
    resetColor();
    std::cout << std::endl;
}