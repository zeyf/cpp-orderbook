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
    std::unordered_map<OrderId, TickerSymbol> _orderIdTickers;
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
        try {
            Order o = _orderbooks[ticker].createOrder(ticker, type, price, quantity, side, exchange);
            _orderIdTickers[o.getOrderId()] = o.getOrderTicker();
        } catch (std::exception &ex) {
            // TODO LOG ERROR
        }
    };

    void cancelOrder(OrderId id) {
        if (!_orderIdTickers.count(id)) {
            std::logic_error("No order is associated with this order ID");
        }

        _orderbooks[_orderIdTickers[id]].cancelOrder(id);
    };
};
