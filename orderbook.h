#include <vector>
#include <list>
#include <memory>
#include <unordered_map>
#include <map>

#include "order.h"
#include "pricing.h"

using PriceLayer = struct PriceLayer {
    std::map<Price, std::list<OrderPointer>, std::greater<Price>> bids;
    std::map<Price, std::list<OrderPointer>, std::less<Price>> asks;
};


class Orderbook {
private:
    std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> _orders;
    PriceLayer _price_layer;
public:
};