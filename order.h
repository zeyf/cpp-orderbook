#include <unordered_map>
#include <random>


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

    OrderId generateOrderId() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dis(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        _id = dis(gen);
    }
public:
    Order(OrderType type, Price price, Quantity quantity, Side side)
        : _type(type), _price(price), _quantity(quantity), _side(side), _id(generateOrderId()) {}


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
    MarketOrder(Price price, Quantity quantity, Side side): Order(OrderType::MARKET, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class MarketOnCloseOrder: public Order {
    MarketOnCloseOrder(Price price, Quantity quantity, Side side): Order(OrderType::MARKET_ON_CLOSE, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class DayOrder: public Order {
    DayOrder(Price price, Quantity quantity, Side side): Order(OrderType::DAY, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};

class GoodTillCancelledOrder: public Order {
    GoodTillCancelledOrder(Price price, Quantity quantity, Side side): Order(OrderType::GOOD_TILL_CANCELLED, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};

class TrailingStopOrder: public Order {
    TrailingStopOrder(Price price, Quantity quantity, Side side): Order(OrderType::TRAILING_STOP, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};

class AllOrNoneOrder: public Order {
    AllOrNoneOrder(Price price, Quantity quantity, Side side): Order(OrderType::ALL_OR_NONE, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};

class FillOrKillOrder: public Order {
    FillOrKillOrder(Price price, Quantity quantity, Side side): Order(OrderType::FILL_OR_KILL, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class BracketOrder: public Order {
    BracketOrder(Price price, Quantity quantity, Side side): Order(OrderType::BRACKET, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class MomentumOrder: public Order {
    MomentumOrder(Price price, Quantity quantity, Side side): Order(OrderType::MOMENTUM, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class StopOrder: public Order {
    StopOrder(Price price, Quantity quantity, Side side): Order(OrderType::STOP, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class ImmediateOrCancelOrder: public Order {
    ImmediateOrCancelOrder(Price price, Quantity quantity, Side side): Order(OrderType::IMMEDIATE_OR_CANCEL, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class ConditionalOrder: public Order {
    ConditionalOrder(Price price, Quantity quantity, Side side): Order(OrderType::CONDITIONAL, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};


class BottomLineOrder: public Order {
    BottomLineOrder(Price price, Quantity quantity, Side side): Order(OrderType::BOTTOM_LINE, price, quantity, side) {}
    void execute() {
        throw std::logic_error("Not implemented");
    };
};
