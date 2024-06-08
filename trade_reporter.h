#include "order.h"
#include "timing.h"


using TradeReport = struct TradeReport {  
    Order bid;
    Order ask;
    Timestamp timestamp;
};

class TradeReporter {
private:
    std::vector<TradeReport> _tradeReports;

public:
    // TODO: Finish design and implement
};
