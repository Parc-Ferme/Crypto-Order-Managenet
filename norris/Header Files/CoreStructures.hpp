#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include <fcntl.h>    // For open()
#include <unistd.h> 
#include "json.hpp"

using String = std::string;

using Time   = std::chrono::seconds;
using Clock  = std::chrono::system_clock;
using Json   = nlohmann::json;

enum class eOrderType {
    
    LIMIT,
    STOP_LIMIT,
    TAKE_LIMIT,
    MARKET,
    STOP_MARKET,
    TAKE_MARKET,
    MARKET_LIMIT,
    TRAILING_STOP,
};

enum class eValidity {
    
    GOOD_TILL_CANCELLED,
    GOOD_TILL_DAY,
    FILL_OR_KILL,
    IMMEDIATE_OR_CANCEL
};

enum class eContractType {
    
    FUTURE,
    OPTION,
    SPOT,
};

enum class eCurrencyType {
    
    BTC,
    ETH,
    USDC,
    USDT,
    EURR,
    any,
};

enum class eDirection {
    
    BUY,
    SELL
};

struct Order {
    
    String     tInstrumentName;
    double     tAmount;
    eOrderType tOrderType;
    String     tLabel;
    double     tPrice;
    eValidity  tValidity;
    eDirection tDirection;
};

#define CHECKNULL(data)  if ((data) == nullptr) { \
                                std::cout << #data << " is NULL" << "\n"; \
                                std::exit(EXIT_FAILURE); \
                               }\

#define CHECKTRUE(condition) if (!(condition)) { \
                                 std::cerr << #condition << " is false" << std::endl; \
                                 std::exit(EXIT_FAILURE); \
                             }


class CoreStructures {
    
public:
    
    template <typename enumType>
    static String label               (enumType pValue);
    
    static void PrintBuyOrderDetails  (String & pResponse);
    static void PrintSellOrderDetails (String & pResponse);
    static void PrintOrderBook        (String & pResponse);
    static void PrintOpenPositions    (String & pResponse);
    static void PrintCurrentPosition  (String & pResponse);
};
