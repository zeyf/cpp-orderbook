#include <cstdint>

#include "order.h"
using TradeId = std::uint64_t;

enum class TradeStatus {
    IN_PROGRESS,
    COMPLETED
};

using Trade = struct Trade {

};

class Trade {
private:
    TradeId _id;
    TradeStatus _status;
    OrderId _bidOrderId;
    OrderId _askOrderId;
    Quantity _filledQuantity;
private:
    [[nodiscard]] TradeId generateTradeId() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dis(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
        return abs(dis(gen));
    }
public:
    Trade(Order &o1, Order &o2, Quantity filledQuantity):
    _id(generateTradeId()), _status(TradeStatus::IN_PROGRESS),
    _filledQuantity(filledQuantity) {
        if (o1.getOrderSide() == OrderSide::BUY) {
            _bidOrderId = o1.getOrderId();
            _askOrderId = o2.getOrderId();
        } else {
            _bidOrderId = o2.getOrderId();
            _askOrderId = o1.getOrderId();
        }
    }

    [[nodiscard]] TradeId getBidTradeId() { return _id; };
    [[nodiscard]] TradeStatus getTradeStatus() { return _status; };
    [[nodiscard]] OrderId getBidOrderId() { return _bidOrderId; };
    [[nodiscard]] OrderId getAskOrderId() { return _askOrderId; };
    [[nodiscard]] Quantity getFilledQuantity() { return _filledQuantity; };
};
