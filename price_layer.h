#include <map>
#include <list>
#include <algorithm>

#include "pricing.h"
#include "order.h"

using PriceLayer = struct PriceLayer {
    std::map<Price, std::list<OrderPointer>, std::greater<Price>> bids;
    std::map<Price, std::list<OrderPointer>, std::less<Price>> asks;
};
