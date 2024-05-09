#include <unordered_map>

#include "side.h"
#include "pricing.h"


using OrderId = std::int64_t;
using OrderSide = Side;


enum class OrderType {
    DAY,
    GOOD_TILL_CANCELLED,
    TRAILING_STOP,
    ALL_OR_NONE,
    FILL_OR_KILL,
    BRACKET,
    MOMENTUM,
    STOP,
    IMMEDIATE_OR_CANCEL,
    CONDITIONAL,
    MARKET,
    BOTTOM_LINE,
    MARKET_ON_CLOSE
};


class Order {
private:
    OrderType _type;
    OrderId _id;
    Side _side;
    Price _price;
    Quantity _quantity;
public:
    Order(OrderType type, OrderId id, Price price, Quantity quantity, Side side) :
        _type(type), _id(id), _price(price), _quantity(quantity), _side(side) {}


    // Getters
    const OrderType getOrderType() const {
        return _type;
    }
    const OrderId getOrderId() const {
        return _id;
    }
    const OrderSide getOrderSide() const {
        return _side;
    }
    const Price getOrderPrice() const {
        return _price;
    }
};


class MarketOrder: public Order {
    MarketOrder(Price price, Quantity quantity, Side side): Order(OrderType::MARKET, 1111, price, quantity, side) {}
    void execute() {

    };
};


class MarketOnCloseOrder: public Order {
    MarketOnCloseOrder(Price price, Quantity quantity, Side side): Order(OrderType::MARKET_ON_CLOSE, 1111, price, quantity, side) {}
    void execute() {

    };
};


class DayOrder: public Order {
    DayOrder(Price price, Quantity quantity, Side side): Order(OrderType::DAY, 1111, price, quantity, side) {}
    void execute() {

    };
};

class GoodTillCancelledOrder: public Order {
    GoodTillCancelledOrder(Price price, Quantity quantity, Side side): Order(OrderType::GOOD_TILL_CANCELLED, 1111, price, quantity, side) {}
    void execute() {

    };
};

class TrailingStopOrder: public Order {
    TrailingStopOrder(Price price, Quantity quantity, Side side): Order(OrderType::TRAILING_STOP, 1111, price, quantity, side) {}
    void execute() {

    };
};

class AllOrNoneOrder: public Order {
    AllOrNoneOrder(Price price, Quantity quantity, Side side): Order(OrderType::ALL_OR_NONE, 1111, price, quantity, side) {}
    void execute() {

    };
};

class FillOrKillOrder: public Order {
    FillOrKillOrder(Price price, Quantity quantity, Side side): Order(OrderType::FILL_OR_KILL, 1111, price, quantity, side) {}
    void execute() {

    };
};


class BracketOrder: public Order {
    BracketOrder(Price price, Quantity quantity, Side side): Order(OrderType::BRACKET, 1111, price, quantity, side) {}
    void execute() {

    };
};


class MomentumOrder: public Order {
    MomentumOrder(Price price, Quantity quantity, Side side): Order(OrderType::MOMENTUM, 1111, price, quantity, side) {}
    void execute() {

    };
};


class StopOrder: public Order {
    StopOrder(Price price, Quantity quantity, Side side): Order(OrderType::STOP, 1111, price, quantity, side) {}
    void execute() {

    };
};


class ImmediateOrCancelOrder: public Order {
    ImmediateOrCancelOrder(Price price, Quantity quantity, Side side): Order(OrderType::IMMEDIATE_OR_CANCEL, 1111, price, quantity, side) {}
    void execute() {

    };
};


class ConditionalOrder: public Order {
    ConditionalOrder(Price price, Quantity quantity, Side side): Order(OrderType::CONDITIONAL, 1111, price, quantity, side) {}
    void execute() {

    };
};


class BottomLineOrder: public Order {
    BottomLineOrder(Price price, Quantity quantity, Side side): Order(OrderType::BOTTOM_LINE, 1111, price, quantity, side) {}
    void execute() {

    };
};


class BottomLineOrder: public Order {
    BottomLineOrder(Price price, Quantity quantity, Side side): Order(OrderType::BOTTOM_LINE, 1111, price, quantity, side) {}
    void execute() {

    };
};
