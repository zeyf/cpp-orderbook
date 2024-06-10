#include <map>
#include <list>
#include <algorithm>

#include "pricing.h"
#include "order.h"


using PricingLayer = struct PricingLayer {
    std::map<Price, std::list<OrderPointer>, std::greater<Price>> bids;
    std::map<Price, std::list<OrderPointer>, std::less<Price>> asks;
};
