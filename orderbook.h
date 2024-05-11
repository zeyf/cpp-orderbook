#include <vector>
#include <list>
#include <memory>
#include <unordered_map>
#include <map>
#include <exception>

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

        OrderPointer orderPtr = order_surface->orderPointer;
        if (orderPtr == nullptr) {
            return;
        }

        if (orderPtr->getOrderSide() == Side::BUY) {
            if (_price_layer.bids.empty()) {
                return;
            }

            std::list<OrderPointer> priceLevelBids = _price_layer.bids[orderPtr->getOrderPrice()];

            if (priceLevelBids.empty()) {
                return;
            }

            priceLevelBids.erase(order_surface->orderPointerSidePriceIterator);
            _orders.erase(id);
        } else if (orderPtr->getOrderSide() == Side::SELL) {
            if (_price_layer.asks.empty()) {
                return;
            }
            
            std::list<OrderPointer> priceLevelAsks = _price_layer.asks[orderPtr->getOrderPrice()];
            if (priceLevelAsks.empty()) {
                return;
            }

            priceLevelAsks.erase(order_surface->orderPointerSidePriceIterator);
            _orders.erase(id);
        }
    }
};