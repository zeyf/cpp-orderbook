#ifndef EXCHANGE_H
#define EXCHANGE_H


#include <unordered_map>

#include "timing.h"
#include "orderbook.h"
#include "exchange_id.h"


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

    std::optional<Order> createOrder(
        TickerSymbol ticker,
        OrderType type,
        Price price,
        Quantity quantity,
        Side side
    ) {
        try {
            Order o = _orderbooks[ticker].createOrder(ticker, type, price, quantity, side, _id);
            _orderIdTickers[o.getOrderId()] = o.getOrderTicker();
            return o;
        } catch (std::exception &ex) {
            // TODO LOG ERROR
        }

        return std::optional<Order>();
    };

    void cancelOrder(OrderId orderId) {
        if (!_orderIdTickers.count(orderId)) {
            std::logic_error("No order is associated with this order ID");
        }

        _orderbooks[_orderIdTickers[orderId]].cancelOrder(orderId);
    };

    std::optional<Order> getOrder(OrderId orderId) {
        if (!_orderIdTickers.count(orderId)) {
            std::logic_error("No order is associated with this order ID");
        }

        return _orderbooks[_orderIdTickers[orderId]].getOrder(orderId);
    }
};

#endif
