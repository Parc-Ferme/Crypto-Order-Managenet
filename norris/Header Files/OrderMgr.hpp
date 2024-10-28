#pragma once

#include "AuthMgr.hpp"

class OrderMgr {
    
public:
    
    static bool InitializeSession  ();
    
    static void EndSession         ();
    
    static bool Validate           ();
    
    static bool PlaceOrder         (const Order pOrder);
    
    static bool CancelOrder        (String pOrderID);
    
    static void CancelAll          ();
    
    static void ModifyOrder        (String pOrderID, double pAmount, double pPrice);
    
    static void GetOrderBook       (String pInstrumentName, int pNumEntries = 10);
    
    static void GetCurrentPosition (eCurrencyType pCurrency, eContractType pContract);
    
private:
    
    static String vOrderPath;
    static String vResponse;
};
