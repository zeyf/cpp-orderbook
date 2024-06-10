#include <vector>
#include <list>
#include <memory>
#include <unordered_map>
#include <map>
#include <optional>

#include "order.h"
#include "pricing.h"
#include "ticker_pricing_layer.h"


class Orderbook {
private:
    std::unordered_map<OrderId, std::shared_ptr<OrderSurface>> _orders;
    TickerPricingLayer _ticker_pricing_layer;
public:
    Order createOrder(TickerSymbol ticker, OrderType type, Price price, Quantity quantity, Side side, ExchangeId exchangeId) {
        Order newOrder = Order(ticker, type, price, quantity, side, exchangeId);
        OrderPointer newOrderPtr = std::make_shared<Order>(newOrder);
        OrderSurface newOrderSurface{newOrderPtr};

        if (side == OrderSide::BUY) {
            _ticker_pricing_layer.at(ticker).bids[price].push_back(newOrderPtr);
            newOrderSurface.orderPointerSidePriceIterator = _ticker_pricing_layer.at(ticker).bids[price].end();
        } else if (side == OrderSide::SELL) {
            _ticker_pricing_layer.at(ticker).asks[price].push_back(newOrderPtr);
            newOrderSurface.orderPointerSidePriceIterator = _ticker_pricing_layer.at(ticker).asks[price].end();
        };

        _orders[newOrder.getOrderId()] = std::make_shared<OrderSurface>(newOrderSurface);
        return newOrder;
    };

    void cancelOrder(OrderId id) {
        if (_orders.empty()) {
            return;
        }
        
        std::shared_ptr<OrderSurface> order_surface = _orders[id];
        if (order_surface == nullptr) {
            return;
        }
        
        OrderPointer orderPtr = order_surface->orderPointer;
        PricingLayer pricingLayer = _ticker_pricing_layer.at(orderPtr->getOrderTicker());
        if (orderPtr->getOrderSide() == Side::BUY) {
            if (pricingLayer.bids.empty()) {
                return;
            }

            std::list<OrderPointer> priceLevelBids = pricingLayer.bids[orderPtr->getOrderPrice()];
            if (priceLevelBids.empty()) {
                return;
            }

            priceLevelBids.erase(order_surface->orderPointerSidePriceIterator);
            _orders.erase(id);
        } else if (orderPtr->getOrderSide() == Side::SELL) {
            if (pricingLayer.asks.empty()) {
                return;
            }
            
            std::list<OrderPointer> priceLevelAsks = pricingLayer.asks[orderPtr->getOrderPrice()];
            if (priceLevelAsks.empty()) {
                return;
            }

            priceLevelAsks.erase(order_surface->orderPointerSidePriceIterator);
            _orders.erase(id);
        }
    }

    [[nodiscard]] std::optional<Order> getOrder(OrderId id) const {
        if (_orders.empty()) {
            return std::optional<Order>();
        }

        OrderPointer orderPtr = _orders.at(id)->orderPointer;
        if (orderPtr == nullptr) {
            return std::optional<Order>();
        }

        return std::optional<Order>(*orderPtr);
    }
};