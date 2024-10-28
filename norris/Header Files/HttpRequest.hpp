#pragma once

#include "Primitves.hpp"

class HttpRequest {
    
public:
    
    static void   Initialize ();
    
    static void   Finalize   ();
    
    static void   AddHeader  (String pHeader);
    
    static bool   Post       (String pPath, String & pResponse);
    
    static size_t Callback   (void * pContent, size_t pSize, size_t pBlock, void* pDataPointer);
    
private:
    
    static struct curl_slist * vHeaders;
    static CURL              * vHandle;
    static CURLcode            vReturnCode;
    static String              vBaseURL;
    static String              clientKey;
    static String              clientSecret;
};
