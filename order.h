#include <unordered_map>
#include <random>
#include <list>

#include "side.h"
#include "pricing.h"


using TickerSymbol = const char *;

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


enum class OrderStatus {
    ACTIVE,
    COMPLETED,
    CANCELLED
};

class Order {
protected:
    TickerSymbol _ticker;
    OrderType _type;
    OrderId _id;
    OrderStatus _status;
    Side _side;
    Price _price;
    Quantity _initial_quantity;
    Quantity _remaining_quantity;
private:
    [[nodiscard]] OrderId generateOrderId() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dis(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        return dis(gen);
    }
public:
    Order(TickerSymbol ticker, OrderType type, Price price, Quantity quantity, Side side):
        _ticker(ticker), _status(OrderStatus::ACTIVE),
        _initial_quantity(quantity), _remaining_quantity(quantity),
        _type(type), _price(price),
        _side(side), _id(generateOrderId()) {}


    // Getters
    const OrderType getOrderType() const {
        return _type;
    }
    const OrderId getOrderId() const {
        return _id;
    }
    const OrderStatus getOrderStatus() const {
        return _status;
    }
    const OrderSide getOrderSide() const {
        return _side;
    }
    const Price getOrderPrice() const {
        return _price;
    }
    const Quantity getOrderInitialQuantity() const {
        return _initial_quantity;
    }
    const Quantity getOrderRemainingQuantity() const {
        return _remaining_quantity;
    }

    [[nodiscard]] virtual bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    virtual void match() {
        throw std::logic_error("Not implemented");
    }
};


using OrderPointer = std::shared_ptr<Order>;

using OrderSurface = struct OrderSurface {
    OrderPointer orderPointer;
    std::list<OrderPointer>::iterator orderPointerSidePriceIterator;
};


class MarketOrder: public Order {
    MarketOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
    : Order(ticker, OrderType::MARKET, price, quantity, side) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};


class MarketOnCloseOrder: public Order {
    MarketOnCloseOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
    : Order(ticker, OrderType::MARKET_ON_CLOSE, price, quantity, side) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};


class DayOrder: public Order {
    DayOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
    : Order(ticker, OrderType::DAY, price, quantity, side) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};

class GoodTillCancelledOrder: public Order {
    GoodTillCancelledOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
    : Order(ticker, OrderType::GOOD_TILL_CANCELLED, price, quantity, side) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    };
};


class FillOrKillOrder: public Order {
    FillOrKillOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
    : Order(ticker, OrderType::FILL_OR_KILL, price, quantity, side) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    };
};

// class TrailingStopOrder: public Order {
//     TrailingStopOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::TRAILING_STOP, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };

// class AllOrNoneOrder: public Order {
//     AllOrNoneOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::ALL_OR_NONE, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class BracketOrder: public Order {
//     BracketOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::BRACKET, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class MomentumOrder: public Order {
//     MomentumOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::MOMENTUM, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class StopOrder: public Order {
//     StopOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::STOP, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class ImmediateOrCancelOrder: public Order {
//     ImmediateOrCancelOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::IMMEDIATE_OR_CANCEL, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class ConditionalOrder: public Order {
//     ConditionalOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::CONDITIONAL, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class BottomLineOrder: public Order {
//     BottomLineOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side)
//     : Order(ticker, OrderType::BOTTOM_LINE, price, quantity, side) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };
