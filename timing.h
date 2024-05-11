#include <chrono>
#include <ctime>

using Timestamp = std::uint64_t;

Timestamp getTimestampInNanosecondsUTC() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
};
