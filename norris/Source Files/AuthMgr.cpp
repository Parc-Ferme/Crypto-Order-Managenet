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

//TODO
bool
AuthMgr::Invalidate ()
{
    return true;
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
        String data;
    
    std::ifstream file (pPath);
    
    // Check if the file opened successfully
    if (!file) {
        std::cout << "Error opening file: " << pPath << "\n";
    }

    std::getline (file, data);

    file.close ();
    
    return data;
}

bool
AuthMgr::IsTokenValid ()
{
    if (Clock::now () >= vExpireTime)
        return false;
        
    return true;
}

