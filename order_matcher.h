#include <thread>

#include "pricing.h"
#include "pricing_layer.h"
#include "side.h"
#include "order.h"
#include "unordered_set"
#include "timing.h"
#include "exchange.h"

#include "trade_reporter.h"
#include "trade_processor.h"


class OrderMatcher {
private:
    std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> &_orders;
    PricingLayer &_pricingLayer;
    TradeProcessor &_tradeProcessor;


    [[nodiscard]] bool canMatch(Order order) {
        OrderSide side = order.getOrderSide();
        OrderType type = order.getOrderType();
        TickerSymbol ticker = order.getOrderTicker();
        Price price = order.getOrderPrice();

        std::unordered_set<OrderSide> expectedOrderSides{OrderSide::BUY, OrderSide::SELL};
        if (!expectedOrderSides.count(side)) {
            throw std::logic_error("Unexpected order type of ... cannot be matched");
        }

        std::list<OrderPointer> bidsAtPrice = _pricingLayer.bids.at(price);
        std::list<OrderPointer> asksAtPrice = _pricingLayer.asks.at(price);

        switch(type) {
            case OrderType::DAY:
                ExchangeId exchange = order.getOrderExchangeId();
                TimeZone exchangeTimeZone = EXCHANGE_ID_TO_TIMEZONE.at(exchange);

                // Cancel order if it is the end of the day
                if (verifyIsAtOrPastDayForTimeZone(exchangeTimeZone)) {
                    // Cancel order
                    order.cancel();
                    return false;
                }

                if (side == OrderSide::BUY) {
                    if (asksAtPrice.empty()) {
                        return false;
                    }

                    for (OrderPointer currentAskOrderPtr: asksAtPrice) {
                        _tradeProcessor.process(order, *currentAskOrderPtr);
                    }
                } else {
                    if (bidsAtPrice.empty()) {
                        return false;
                    }

                    for (OrderPointer currentBidOrderPtr: bidsAtPrice) {
                        _tradeProcessor.process(order, *currentBidOrderPtr);
                    }
                }
            case OrderType::MARKET_ON_CLOSE:
                throw std::logic_error("This order type is not implemented");
            case OrderType::FILL_OR_KILL:
                throw std::logic_error("This order type is not implemented");
            case OrderType::GOOD_TILL_CANCELLED:
                throw std::logic_error("This order type is not implemented");
        }

        return false;
    }

    void listen() {
        // TODO: Implement listening thread
    }
public:
    OrderMatcher(
        std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> &orders,
        PricingLayer &pricingLayer,
        TradeProcessor &tradeProcessor
    ):
    _orders(orders),
    _pricingLayer(pricingLayer),
    _tradeProcessor(tradeProcessor) {}
};