#include "HttpRequest.hpp"

struct curl_slist * HttpRequest::vHeaders;
CURL              * HttpRequest::vHandle;
CURLcode            HttpRequest::vReturnCode;
String              HttpRequest::vBaseURL;

void
HttpRequest::Initialize ()
{
    vBaseURL = "https://test.deribit.com";
    vHandle  = curl_easy_init ();
    
    CHECKNULL (vHandle);
    
    vHeaders = curl_slist_append (vHeaders, "Content-Type: application/json");
    
    CHECKNULL (vHeaders);
    
    return;
}

void
HttpRequest::Finalize ()
{
    // At time of finalization these paramter shouldn't be nullptr.
    CHECKNULL (vHandle);
    CHECKNULL (vHeaders);
    
    curl_easy_cleanup (vHandle);
    curl_slist_free_all (vHeaders);
}

void
HttpRequest::AddHeader (String pHeader)
{
    vHeaders = curl_slist_append (vHeaders, pHeader.c_str());
    
    CHECKNULL (vHeaders);
}

bool
HttpRequest::Post (String pPath, String & pResponse)
{
        
        String path;
    
    path = vBaseURL + pPath;
    
    curl_easy_setopt (vHandle, CURLOPT_URL, path.c_str ());

    curl_easy_setopt (vHandle, CURLOPT_HTTPHEADER, vHeaders);
    
    curl_easy_setopt (vHandle, CURLOPT_WRITEFUNCTION, Callback);
    curl_easy_setopt (vHandle, CURLOPT_WRITEDATA, &pResponse);
        
    vReturnCode = curl_easy_perform (vHandle);
    
    if(vReturnCode != CURLE_OK) {
        
        printf("Request Failed: %s\n", curl_easy_strerror (vReturnCode));
        return false;
    }
    
    return true;
}

size_t
HttpRequest::Callback (void * pContent, size_t pSize, size_t pBlock, void * pDataPointer)
{
    ((String *)pDataPointer)->append((char *)pContent, pSize * pBlock);
    return pSize * pBlock;
}
