#include "timing.h"
#include <unordered_map>

enum class ExchangeId {
    NYSE,
    NASDAQ
};

std::unordered_map<ExchangeId, TimeZone> EXCHANGE_ID_TO_TIMEZONE{
    {ExchangeId::NYSE, TimeZone::EST},
    {ExchangeId::NASDAQ, TimeZone::EST}
};

class Exchange {
private:
    ExchangeId _id;
    TimeZone _timezone;
    std::unordered_map<TickerSymbol, Orderbook> _orderbooks;
public:
    Exchange(ExchangeId id):
    _id(id),
    _timezone(EXCHANGE_ID_TO_TIMEZONE.at(id)) {}

    void createOrder(
        TickerSymbol ticker,
        OrderType type,
        Price price,
        Quantity quantity,
        Side side,
        Exchange exchange
    ) {
        _orderbooks[ticker].createOrder(ticker, type, price, quantity, side, exchange);
    };
};
