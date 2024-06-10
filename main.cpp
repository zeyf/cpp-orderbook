#include <iostream>
#include <algorithm>
#include <format>
#include <iostream>

#include "orderbook.h"

int main() {
    Exchange nyseExchange(ExchangeId::NYSE);

    std::optional<Order> o1 = nyseExchange.createOrder(
        "GOOG",
        OrderType::DAY,
        150,
        10,
        OrderSide::BUY
    );

    if (o1.has_value()) {
        OrderId id = o1.value().getOrderId();
        nyseExchange.cancelOrder(id);
        std::optional<Order> o1Re = nyseExchange.getOrder(id);

        std::cout << (o1Re.has_value() ? "WTF" : "Deleted") << "\n";
    }

    return 0;
}
