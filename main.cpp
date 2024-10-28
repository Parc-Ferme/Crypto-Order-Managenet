#include "OrderMgr.hpp"

int main()
{
    OrderMgr::InitializeSession();
    
    //Order buyOrder {"BTC-PERPETUAL", 20, eOrderType::LIMIT, "first-order", 67000.50, eValidity::GOOD_TILL_DAY, eDirection::BUY};

    //OrderMgr::PlaceOrder(buyOrder);

    OrderMgr::GetOrderBook("BTC-PERPETUAL");
//
//    OrderMgr::GetCurrentPosition(eCurrencyType::BTC, eContractType::FUTURE);
//    
//    OrderMgr::CancelOrder("29207060941");
//    
//    OrderMgr::ModifyOrder("29203747664", 15, 68000);
//    
//    OrderMgr::CancelAll();
//    
//    OrderMgr::GetOpenOrders();
    
    return 0;
}
