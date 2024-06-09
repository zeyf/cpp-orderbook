#include <cmath>
#include <tuple>

#include "trade.h"
#include "trade_reporter.h"
#include "order.h"


class TradeProcessor {
private:
    TradeReporter _tradeReporter;

    [[nodiscard]] const std::tuple<OrderFillCapacityType, OrderFillCapacityType, Quantity> _getFillableCapacityTypesAndQuantity(Order &o1, Order &o2) {
        // If it is 0, something is terribly wrong. LOL
        Quantity fillableQuantity = std::min(o1.getOrderRemainingQuantity(), o2.getOrderRemainingQuantity());

        OrderFillCapacityType o1fillableCapacityType = (
            o1.getOrderRemainingQuantity() == fillableQuantity ? OrderFillCapacityType::FULL : OrderFillCapacityType::PARTIAL
        ), o2fillableCapacityType = (
            o2.getOrderRemainingQuantity() == fillableQuantity ? OrderFillCapacityType::FULL : OrderFillCapacityType::PARTIAL
        );

        return std::tuple<OrderFillCapacityType, OrderFillCapacityType, Quantity>{
            o1fillableCapacityType,
            o2fillableCapacityType,
            fillableQuantity
        };
    }
public:
    std::tuple<
        Trade,
        std::pair<OrderFillCapacityType, Price>,
        std::pair<OrderFillCapacityType, Price>
    > process(Order &o1, Order &o2) {
        Order &bidOrder = o1.getOrderSide() == OrderSide::BUY ? o1 : o2;
        Order &askOrder = o1.getOrderSide() == OrderSide::SELL ? o1 : o2;

        if (bidOrder.getOrderSide() == askOrder.getOrderSide()) {
            std::logic_error("A trade cannot happen with 2 orders on the same side");
        }

        std::tuple<OrderFillCapacityType, OrderFillCapacityType, Quantity> fillableOrderContext = _getFillableCapacityTypesAndQuantity(o1, o2);
        Quantity fillableQuantity = std::get<2>(fillableOrderContext);

        Trade newTrade = Trade(o1, o2, fillableQuantity);
        std::pair<OrderFillCapacityType, Price>
            o1PostFillContext = o1.fill(fillableQuantity),
            o2PostFillContext = o2.fill(fillableQuantity);
        
        // TODO: Implement trade reporting
        //_tradeReporter.report(newTrade);
        return {newTrade, o1PostFillContext, o2PostFillContext};
    }

};
