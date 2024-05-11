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
    void createOrder() {};

    void modifyOrder() {};

    void cancelOrder(OrderId id) {
        if (_orders.empty()) {
            return;
        }
        
        std::shared_ptr<OrderSurface> order_surface = _orders[id];

        if (order_surface == nullptr) {
            return;
        }

        if (order_surface->side == Side::BUY) {
            if (_price_layer.bids.empty()) {
                return;
            }

            std::list<OrderPointer> priceLevelBids = _price_layer.bids[order_surface->price];

            if (priceLevelBids.empty()) {
                return;
            }

            priceLevelBids.erase(order_surface->iterator);
            _orders.erase(id);
        } else if (order_surface->side == Side::SELL) {
            if (_price_layer.asks.empty()) {
                return;
            }
            
            std::list<OrderPointer> priceLevelAsks = _price_layer.asks[order_surface->price];
            if (priceLevelAsks.empty()) {
                return;
            }

            priceLevelAsks.erase(order_surface->iterator);
            _orders.erase(id);
        }
    }
};