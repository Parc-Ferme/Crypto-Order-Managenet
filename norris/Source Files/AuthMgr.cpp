#include "AuthMgr.hpp"

String            AuthMgr::vAccessToken;
String            AuthMgr::vClientKey;
String            AuthMgr::vClientSecret;
String            AuthMgr::vRefreshToken;
Clock::time_point AuthMgr::vExpireTime;

bool
AuthMgr::Authenticate ()
{
        String pathUrl;
        String response;
        int    expireIn;
        bool   retval;
        Json   parsedJSON;
    
    HttpRequest::Initialize();
    
    vClientKey    = ReadFile ("/Users/ankit/Desktop/norris/clientKey.txt");
    vClientSecret = ReadFile ("/Users/ankit/Desktop/norris/clientSecret.txt");
    
    pathUrl = "/api/v2/public/auth?client_id=" + vClientKey + "&client_secret=" + vClientSecret + "&grant_type=client_credentials";
    
    retval = HttpRequest::Post (pathUrl, response);
    
    if (retval == false)
        return false;
    
    //parse the response to get sepcific data..
    parsedJSON = Json::parse (response);

    // Access specific fields
    vRefreshToken = parsedJSON["result"]["refresh_token"];
    vAccessToken  = parsedJSON["result"]["access_token"];
    expireIn      = parsedJSON["result"]["expires_in"];
    
    vExpireTime = Clock::now () + Time(expireIn);

    return true;
}

void
AuthMgr::Invalidate ()
{
    HttpRequest::Finalize ();
}


bool
AuthMgr::RevalidateAccessToken ()
{
        String pathurl;
        String response;
        int    expireIn;
        bool   retval;
        Json   parsedJSON;
    
    pathurl = "/api/v2/public/auth?grant_type=refresh_token&refresh_token=" + vRefreshToken + "&client_id=" + vClientKey + "&client_secret=" + vClientSecret;
    
    retval = HttpRequest::Post (pathurl, response);
    
    if (retval == false)
        return false;
    
    parsedJSON = Json::parse (response);
    
    // Update required data
    vRefreshToken = parsedJSON["result"]["refresh_token"];
    vAccessToken  = parsedJSON["result"]["access_token"];
    expireIn      = parsedJSON["result"]["expires_in"];
    
    vExpireTime = Clock::now () + Time(expireIn);
    
    return true;
}

String
AuthMgr::GetAccessToken ()
{
    return vAccessToken;
}

String
AuthMgr::ReadFile (String pPath)
{
        int     fileDescriptor;
        size_t  retval;
        char    buffer[512];
        size_t  bufferSize;

    bufferSize = 512;
    
    // Open a file for reading and writing
    fileDescriptor = open (pPath.c_str(), O_RDWR);

    //Error Handling
    
    if (fileDescriptor == -1) {
        printf("Error while opening client file: %d", errno);
    }

    // Seek to the beginning of the file
    retval = lseek (fileDescriptor, 0, SEEK_SET);

    //Error Handling
    if (retval == -1) {
        printf("Error setting off-set in client file: %d", errno);
    }
    
    // Read from the file
    retval = read (fileDescriptor, buffer, bufferSize - 1);
    
    //Error Handling
    if (retval == -1) {
        printf("Error setting off-set in client file: %d", errno);
    }
    
    buffer[retval] = '\0';
    
    retval = close (fileDescriptor);
    
    //Error Handling
    if (retval == -1) {
        printf("Error setting off-set in client file: %d", errno);
    }
    
    return buffer;
}

bool
AuthMgr::IsTokenValid ()
{
    return Clock::now () >= vExpireTime;
}
