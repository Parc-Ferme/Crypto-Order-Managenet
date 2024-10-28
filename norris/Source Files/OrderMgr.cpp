#include "OrderMgr.hpp"

String OrderMgr::vOrderPath;
String OrderMgr::vResponse;

bool
OrderMgr::InitializeSession ()
{
        String header;
    
    if (AuthMgr::Authenticate () == false)
        return false;
    
    header = "Authorization: Bearer " + AuthMgr::GetAccessToken();
    
    HttpRequest::AddHeader (header);
    
    vOrderPath = "/api/v2";
    
    return true;
}

bool
OrderMgr::EndSession ()
{
    return AuthMgr::Invalidate ();
}

void
OrderMgr::PlaceOrder (const Order pOrder)
{
        bool   retval;
        char   buffer[256];
        size_t bufferSize;
    
    bufferSize = 256;
    
    retval = AuthMgr::IsTokenValid ();
    
    if (retval == false)
        AuthMgr::RevalidateAccessToken();
    
    if (pOrder.tDirection == eDirection::BUY)
        vOrderPath += "/private/buy?";
    else
        vOrderPath += "/private/sell?";
    
    snprintf (buffer, bufferSize, "amount=%.2f&instrument_name=%s&label=%s&price=%.2f&type=%s",pOrder.tAmount, pOrder.tInstrumentName.c_str(),
              pOrder.tLabel.c_str(), pOrder.tPrice, CoreStructures::label(pOrder.tOrderType).c_str());
        
    vOrderPath += buffer;

    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintBuyOrderDetails(vResponse);
}

void
OrderMgr::CancelOrder(String pOrderID)
{
    vOrderPath += "/private/cancel?order_id=" + pOrderID;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    std::cout << "Number of Cancelled Order: \n" << Json::parse(vResponse)["result"] << "\n";
}

void
OrderMgr::CancelAll ()
{
    vOrderPath += "/private/cancel_all?";
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    std::cout << "Number of Cancelled Order: \n" << Json::parse(vResponse)["result"] << "\n";
}

void
OrderMgr::ModifyOrder (String pOrderID, double pAmount, double pPrice)
{
        char buffer[64];
        size_t bufferSize;
    
    bufferSize = 64;
    
    snprintf (buffer, bufferSize, "/private/edit?order_id=%s&amount=%.2f&price=%.2f", pOrderID.c_str(), pAmount, pPrice);
    
    vOrderPath += buffer;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintBuyOrderDetails (vResponse);
}

void
OrderMgr::GetOpenOrders ()
{
    vOrderPath += "/private/get_open_orders?";
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintOpenPositions (vResponse);
}

void
OrderMgr::GetOrderBook (String pInstrumentName, int pNumEntries)
{
        char buffer[64];
        size_t bufferSize;

    bufferSize = 64;

    snprintf (buffer, bufferSize, "/public/get_order_book?instrument_name=%s&depth=%u", pInstrumentName.c_str(), pNumEntries);

    vOrderPath += buffer;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintOrderBook (vResponse);
    
}

void
OrderMgr::GetCurrentPosition (eCurrencyType pCurrency, eContractType pContract)
{
    vOrderPath += "/private/get_positions?currency=" + CoreStructures::label (pCurrency) + "&kind=" + CoreStructures::label (pContract);
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintCurrentPosition (vResponse);
}
