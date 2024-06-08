#include <unordered_map>
#include <random>
#include <list>
#include <chrono>
#include <math.h>


#include "timing.h"
#include "side.h"
#include "pricing.h"
#include "exchange.h"

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

enum class OrderFillCapacity {
    FULL,
    PARTIAL
};

class Order {
protected:
    TickerSymbol _ticker;
    Exchange _exchange;
    OrderType _type;
    OrderId _id;
    Timestamp _timestamp;
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
        return abs(dis(gen));
    }
public:
    Order(TickerSymbol ticker, OrderType type, Price price, Quantity quantity, Side side, Exchange exchange):
        _ticker(ticker), _status(OrderStatus::ACTIVE),
        _initial_quantity(quantity), _remaining_quantity(quantity),
        _type(type), _price(price),
        _side(side), _id(generateOrderId()),
        _timestamp(getTimestampInNanosecondsUTC()),
        _exchange(exchange) {}


    // Getters
    [[nodiscard]] const TickerSymbol getOrderTicker() const { return _ticker; }
    [[nodiscard]] const Exchange getOrderExchange() const { return _exchange; }
    [[nodiscard]] const OrderType getOrderType() const { return _type; }
    [[nodiscard]] const OrderId getOrderId() const { return _id; }
    [[nodiscard]] const Timestamp getTimestamp() const { return _timestamp; }
    [[nodiscard]] const OrderStatus getOrderStatus() const { return _status; }
    [[nodiscard]] const OrderSide getOrderSide() const { return _side; }
    [[nodiscard]] const Price getOrderPrice() const { return _price; }
    [[nodiscard]] const Quantity getOrderInitialQuantity() const { return _initial_quantity; }
    [[nodiscard]] const Quantity getOrderRemainingQuantity() const { return _remaining_quantity; }
    [[nodiscard]] const std::pair<OrderFillCapacity, Quantity> getFillableQuantity(Quantity q) {
        if (_remaining_quantity <= q) {
            return std::pair<OrderFillCapacity, Quantity>{OrderFillCapacity::FULL, _remaining_quantity};
        } else {
            return std::pair<OrderFillCapacity, Quantity>{OrderFillCapacity::PARTIAL, _remaining_quantity - q};
        }
    }

    // TODO
    void cancel() {
        _status = OrderStatus::CANCELLED;
    }

    // TODO
    void complete() {
        _status = OrderStatus::COMPLETED;
    }
};


using OrderPointer = std::shared_ptr<Order>;

using OrderSurface = struct OrderSurface {
    OrderPointer orderPointer;
    std::list<OrderPointer>::iterator orderPointerSidePriceIterator;
};


class MarketOrder: public Order {
    MarketOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
    : Order(ticker, OrderType::MARKET, price, quantity, side, exchange) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};


class MarketOnCloseOrder: public Order {
    MarketOnCloseOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
    : Order(ticker, OrderType::MARKET_ON_CLOSE, price, quantity, side, exchange) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};


class DayOrder: public Order {
    DayOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
    : Order(ticker, OrderType::DAY, price, quantity, side, exchange) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    }
};

class GoodTillCancelledOrder: public Order {
    GoodTillCancelledOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
    : Order(ticker, OrderType::GOOD_TILL_CANCELLED, price, quantity, side, exchange) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    };
};


class FillOrKillOrder: public Order {
    FillOrKillOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
    : Order(ticker, OrderType::FILL_OR_KILL, price, quantity, side, exchange) {}

    [[nodiscard]] bool canMatch() {
        throw std::logic_error("Not implemented");
    }
    void match() {
        throw std::logic_error("Not implemented");
    };
};


// class TrailingStopOrder: public Order {
//     TrailingStopOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::TRAILING_STOP, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };

// class AllOrNoneOrder: public Order {
//     AllOrNoneOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::ALL_OR_NONE, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class BracketOrder: public Order {
//     BracketOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::BRACKET, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class MomentumOrder: public Order {
//     MomentumOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::MOMENTUM, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class StopOrder: public Order {
//     StopOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::STOP, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class ImmediateOrCancelOrder: public Order {
//     ImmediateOrCancelOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::IMMEDIATE_OR_CANCEL, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class ConditionalOrder: public Order {
//     ConditionalOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::CONDITIONAL, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };


// class BottomLineOrder: public Order {
//     BottomLineOrder(TickerSymbol ticker, Price price, Quantity quantity, Side side, Exchange exchange)
//     : Order(ticker, OrderType::BOTTOM_LINE, price, quantity, side, exchange) {}
//     void match() {
//         throw std::logic_error("Not implemented");
//     };
// };
