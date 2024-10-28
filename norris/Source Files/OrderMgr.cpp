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
        return AuthMgr::RevalidateAccessToken ();
    
    return true;
}

bool
OrderMgr::PlaceOrder (const Order pOrder)
{
        bool   retval;
        char   buffer[256];
        size_t bufferSize;
        String URL;
    
    bufferSize = 256;
    URL = vOrderPath;
    
    vResponse.clear();
    
    retval = Validate ();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return false;
    }
    
    if (pOrder.tDirection == eDirection::BUY)
        URL += "/private/buy?";
    else
        URL += "/private/sell?";
    
    snprintf (buffer, bufferSize, "amount=%.2f&instrument_name=%s&label=%s&price=%.2f&type=%s",pOrder.tAmount,
              pOrder.tInstrumentName.c_str(), pOrder.tLabel.c_str(), pOrder.tPrice,
              Primitves::label(pOrder.tOrderType).c_str());
        
    URL += buffer;

    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return false;
        
    Primitves::PrintOrderDetails (vResponse);

    return true;
}

bool
OrderMgr::CancelOrder (String pOrderID)
{
        bool   retval;
        String URL;
    
    URL = vOrderPath;
    
    vResponse.clear();
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return false;
    }
    
    URL += "/private/cancel?order_id=" + pOrderID;
    
    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return false;

    Primitves::PrintCancelOrderDetail (vResponse);
    
    return true;
}

void
OrderMgr::CancelAll ()
{
        bool   retval;
        String URL;
    
    URL = vOrderPath;
    
    vResponse.clear();
    
    retval = Validate ();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    URL += "/private/cancel_all?";
    
    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return;
    
    Primitves::PrintCancelOrderCount (vResponse);
}

void
OrderMgr::ModifyOrder (String pOrderID, double pAmount, double pPrice)
{
        char   buffer[64];
        size_t bufferSize;
        bool   retval;
        String URL;
    
    bufferSize = 64;
    URL = vOrderPath;
    
    vResponse.clear();

    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    // I have set the buffer size to 64 based on my estimation of the maximum required capacity.
    // Therefore, I did not include any additional checks
    snprintf (buffer, bufferSize, "/private/edit?order_id=%s&amount=%.2f&price=%.2f", pOrderID.c_str(), pAmount, pPrice);
    
    URL += buffer;
    
    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return;
    
    Primitves::PrintOrderDetails (vResponse);
}

void
OrderMgr::GetOrderBook (String pInstrumentName, int pNumEntries)
{
        char   buffer[64];
        size_t bufferSize;
        String URL;

    bufferSize = 64;
    URL = vOrderPath;
    
    vResponse.clear ();

    // I have set the buffer size to 64 based on my estimation of the maximum required capacity.
    // Therefore, I did not include any additional checks
    snprintf (buffer, bufferSize, "/public/get_order_book?instrument_name=%s&depth=%u", pInstrumentName.c_str(), pNumEntries);

    URL += buffer;
    
    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return;
    
    Primitves::PrintOrderBook (vResponse);
}

void
OrderMgr::GetCurrentPosition (eCurrencyType pCurrency, eContractType pContract)
{
        bool retval;
        String URL;
    
    URL = vOrderPath;
    
    vResponse.clear();
    
    retval = Validate();
    
    if (retval == false) {
        
        printf ("Token isn't valid and Revalidation Failed, Please the Id and Secret.");
        return;
    }
    
    URL += "/private/get_positions?currency=" + Primitves::label (pCurrency) + "&kind=" +
            Primitves::label (pContract);
    
    HttpRequest::Post (URL, vResponse);
    
    if (Primitves::CheckResponse (vResponse))
        return;
    
    Primitves::PrintCurrentPosition (vResponse);
}
