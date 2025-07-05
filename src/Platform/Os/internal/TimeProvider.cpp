#include "TimeProvider.h"

#include <chrono>

DateTime TimeProvider::getCurrentTimestamp() const {
    auto now {std::chrono::system_clock::now()};
    auto epoch {now.time_since_epoch()};
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::seconds>(epoch).count());
}