#pragma once

#include "HttpRequest.hpp"

class AuthMgr {
    
public:
    static bool   Authenticate          ();
    static void   Invalidate            ();
    static bool   RevalidateAccessToken ();
    static String GetAccessToken        ();
    static String ReadFile              (String pPath);
    static bool   IsTokenValid          ();

private:
    static String            vAccessToken;
    static String            vClientKey;
    static String            vClientSecret;
    static String            vRefreshToken;
    static Clock::time_point vExpireTime;
};
