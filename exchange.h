#include "timing.h"
#include <unordered_map>

enum class Exchange {
    NYSE,
    NASDAQ
};

std::unordered_map<Exchange, TimeZone> EXCHANGE_TO_TIMEZONE{
    {Exchange::NYSE, TimeZone::EST},
    {Exchange::NASDAQ, TimeZone::EST}
};
