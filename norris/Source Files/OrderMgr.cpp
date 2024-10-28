#include "OrderMgr.hpp"

String OrderMgr::vOrderPath;
String OrderMgr::vResponse;

bool
OrderMgr::InitializeSession ()
{
        String header;
    
    if (AuthMgr::Authenticate () == false) {
        
        printf ("Authentication isn't successfull, Please the Id and Secret.");
        return false;
    }
    
    header = "Authorization: Bearer " + AuthMgr::GetAccessToken();
    
    HttpRequest::AddHeader (header);
    
    vOrderPath = "/api/v2";
    
    return true;
}

void
OrderMgr::EndSession ()
{
    AuthMgr::Invalidate ();
}

bool
OrderMgr::Validate ()
{
        bool retval;
    
    retval = AuthMgr::IsTokenValid ();
    
    if (retval == false)
        return AuthMgr::RevalidateAccessToken();
    
    return true;
}

bool
OrderMgr::PlaceOrder (const Order pOrder)
{
        bool   retval;
        char   buffer[256];
        size_t bufferSize;
    
    bufferSize = 256;
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return false;
    }
    
    if (pOrder.tDirection == eDirection::BUY)
        vOrderPath += "/private/buy?";
    else
        vOrderPath += "/private/sell?";
    
    snprintf (buffer, bufferSize, "amount=%.2f&instrument_name=%s&label=%s&price=%.2f&type=%s",pOrder.tAmount,
              pOrder.tInstrumentName.c_str(), pOrder.tLabel.c_str(), pOrder.tPrice,
              CoreStructures::label(pOrder.tOrderType).c_str());
        
    vOrderPath += buffer;

    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintBuyOrderDetails(vResponse);
    
    return true;
}

bool
OrderMgr::CancelOrder(String pOrderID)
{
        bool   retval;
        size_t orderCount;
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return false;
    }
    
    vOrderPath += "/private/cancel?order_id=" + pOrderID;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    orderCount = Json::parse(vResponse)["result"];
    
    printf ("Number of Cancelled Order: %zu\n", orderCount);
    
    return true;
}

void
OrderMgr::CancelAll ()
{
        bool   retval;
        size_t orderCount;
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    vOrderPath += "/private/cancel_all?";
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    orderCount = Json::parse(vResponse)["result"];
    
    printf ("Number of Cancelled Order: %zu\n", orderCount);
}

void
OrderMgr::ModifyOrder (String pOrderID, double pAmount, double pPrice)
{
        char buffer[64];
        size_t bufferSize;
        bool retval;
    
    bufferSize = 64;

    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    //TODO: Error Handling
    snprintf (buffer, bufferSize, "/private/edit?order_id=%s&amount=%.2f&price=%.2f", pOrderID.c_str(), pAmount, pPrice);
    
    vOrderPath += buffer;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintBuyOrderDetails (vResponse);
}

void
OrderMgr::GetOpenOrders ()
{
        bool retval;
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
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

    //TODO: Error Handling
    snprintf (buffer, bufferSize, "/public/get_order_book?instrument_name=%s&depth=%u", pInstrumentName.c_str(), pNumEntries);

    vOrderPath += buffer;
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintOrderBook (vResponse);
}

void
OrderMgr::GetCurrentPosition (eCurrencyType pCurrency, eContractType pContract)
{
        bool retval;
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    vOrderPath += "/private/get_positions?currency=" + CoreStructures::label (pCurrency) + "&kind=" + CoreStructures::label (pContract);
    
    HttpRequest::Post (vOrderPath, vResponse);
    
    CoreStructures::PrintCurrentPosition (vResponse);
}
