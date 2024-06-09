#include <chrono>
#include <ctime>

using Timestamp = std::uint64_t;

enum class TimeZone {
    EST,
    PST
};

[[nodiscard]] Timestamp getTimestampInNanosecondsUTC() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
};

[[nodiscard]] bool verifyIsAtOrPastDayForTimeZone(TimeZone timeZone) {
    Timestamp now = getTimestampInNanosecondsUTC();
    std::time_t utcSeconds = now / 1000000000;
    std::tm* utcTime = std::gmtime(&utcSeconds);

    if (timeZone == TimeZone::EST) {
        // Convert to EST by subtracting 5 hours
        std::time_t estSeconds = utcSeconds - (5 * 3600);

        // Convert to EST time struct for UTC
        std::tm* estTime = std::gmtime(&estSeconds);

        // Check if the adjusted time is 4:00 PM
        return (
            estTime->tm_hour >= 16
            && estTime->tm_min >= 0
            && estTime->tm_sec >= 0
        );
    } else {
        // TODO: Add time zone and consider if this warrants a throw?
        // std::logic_error("This time zone is not supported");
        return false;
    }
};
