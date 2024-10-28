#pragma once

#include "AuthMgr.hpp"

class OrderMgr {
    
public:
    
    static bool InitializeSession  ();
    
    static bool EndSession         ();
    
    static void PlaceOrder         (const Order pOrder);
    
    static void CancelOrder        (String pOrderID);
    
    static void CancelAll          ();
    
    static void ModifyOrder        (String pOrderID, double pAmount, double pPrice);
    
    static void GetOpenOrders      ();
    
    static void GetOrderBook       (String pInstrumentName, int pNumEntries = 10);
    
    static void GetCurrentPosition (eCurrencyType pCurrency, eContractType pContract);
    
private:
    
    static String vOrderPath;
    static String vResponse;
};
