#include <thread>

#include "pricing.h"
#include "price_layer.h"
#include "side.h"
#include "order.h"
#include "unordered_set"
#include "timing.h"
#include "exchange.h"

#include "trade_reporter.h"

class OrderMatcher {
private:
    std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> &_orders;
    PriceLayer &_priceLayer;
    TradeReporter &_tradeReporter;


    [[nodiscard]] bool canMatch(Order order) {
        OrderSide side = order.getOrderSide();
        OrderType type = order.getOrderType();
        Price price = order.getOrderPrice();

        std::unordered_set<OrderSide> expectedOrderSides{OrderSide::BUY, OrderSide::SELL};
        if (!expectedOrderSides.count(side)) {
            throw std::logic_error("Unexpected order type of ... cannot be matched");
        }

        std::list<OrderPointer> bidsAtPrice = _priceLayer.bids.at(price);
        std::list<OrderPointer> asksAtPrice = _priceLayer.asks.at(price);

        switch(type) {
            case OrderType::DAY:
                Exchange exchange = order.getOrderExchange();
                TimeZone exchangeTimeZone = EXCHANGE_TO_TIMEZONE.at(exchange);

                // Cancel order if it is the end of the day
                if (verifyIsEndOfDayForTimeZone(exchangeTimeZone)) {
                    // Cancel order
                    order.cancel();
                    return false;
                }

                if (side == OrderSide::BUY) {
                    if (asksAtPrice.empty()) {
                        return false;
                    }

                    Quantity remainingBidOrderQuantity = order.getOrderRemainingQuantity();
                    for (OrderPointer currentAskOrderPtr: asksAtPrice) {
                        std::pair<OrderFillCapacity, Quantity> fillableContext = currentAskOrderPtr->getFillableQuantity(remainingBidOrderQuantity);
                        
                        // Zero out both orders, report on TradeReporter
                        if (fillableContext.first == OrderFillCapacity::FULL) {

                        // Zero out one order, remove from the other, report on TradeReporter
                        } else {

                        };
                    }
                } else {
                    if (bidsAtPrice.empty()) {
                        return false;
                    }

                    for (OrderPointer bidOrderPtr: bidsAtPrice) {

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

    void match() {

    }
public:
    OrderMatcher(
        std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> &orders,
        PriceLayer &priceLayer,
        TradeReporter &tradeReporter
    ): _orders(orders), _priceLayer(priceLayer), _tradeReporter(tradeReporter) {}
};