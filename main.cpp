#include "OrderMgr.hpp"

int main()
{
    OrderMgr::InitializeSession();
    
    Order buyOrder {"ETH-PERPETUAL", 2, eOrderType::LIMIT, "Market1", 2320, eValidity::GOOD_TILL_CANCELLED, eDirection::BUY};

    OrderMgr::PlaceOrder (buyOrder);

    OrderMgr::GetOrderBook("ETH-PERPETUAL");

     OrderMgr::GetCurrentPosition(eCurrencyType::BTC, eContractType::FUTURE);

    OrderMgr::CancelOrder("ETH-14387089701");

    OrderMgr::ModifyOrder("ETH-14386879208", 3, 2300);
    
    OrderMgr::CancelAll();
    
    return 0;
}
