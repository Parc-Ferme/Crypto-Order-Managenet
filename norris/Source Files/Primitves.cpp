#include "Primitves.hpp"


template<>
String
Primitves::label (eContractType pValue)
{
    switch (pValue) {
        case eContractType::FUTURE:
            return "future";
            break;
            
        case eContractType::OPTION:
            return "option";
            break;
            
        case eContractType::SPOT:
            return "spot";
            break;
            
        default:
            return "";
    }
}

template<>
String
Primitves::label (eCurrencyType pValue)
{
    switch (pValue) {
        case eCurrencyType::BTC:
            return "BTC";
            break;
            
        case eCurrencyType::ETH:
            return "ETH";
            break;
            
        case eCurrencyType::USDC:
            return "USDC";
            break;
            
        case eCurrencyType::USDT:
            return "USDT";
            break;
            
        case eCurrencyType::EURR:
            return "EURR";
            break;
            
        case eCurrencyType::any:
            return "any";
            break;
            
        default:
            break;
    }
}

template<>
String
Primitves::label (eOrderType pValue)
{
    switch (pValue) {
        case eOrderType::LIMIT:
            return "limit";
            break;
            
        case eOrderType::STOP_LIMIT:
            return "stop_limit";
            break;
            
        case eOrderType::TAKE_LIMIT:
            return "take_limit";
            break;
            
        case eOrderType::MARKET:
            return "market";
            break;
            
        case eOrderType::STOP_MARKET:
            return "stop_market";
            break;
            
        case eOrderType::TAKE_MARKET:
            return "take_market";
            break;
            
        case eOrderType::MARKET_LIMIT:
            return "market_limit";
            break;
            
        case eOrderType::TRAILING_STOP:
            return "trailing_stop";
            break;
            
        default:
            break;
    }
}

template<>
String
Primitves::label (eValidity pValue)
{
    switch (pValue) {
        case eValidity::GOOD_TILL_CANCELLED:
            return "good_till_cancelled";
            break;
            
        case eValidity::GOOD_TILL_DAY:
            return "good_till_day";
            break;
            
        case eValidity::FILL_OR_KILL:
            return "fill_or_kill";
            break;
            
        case eValidity::IMMEDIATE_OR_CANCEL:
            return "immediate_or_cancel";
            break;
            
        default:
            break;
    }
}

template<>
String
Primitves::label (eDirection pValue)
{
    switch (pValue) {
        case eDirection::BUY:
            return "buy";
            break;
            
        case eDirection::SELL:
            return "sell";
            break;
            
        default:
            break;
    }
}

void
Primitves::PrintOrderDetails (String & pResponse)
{
        Json jsonData;
    
    jsonData = Json::parse (pResponse);
    
    std::cout << "Order Details:\n";
    std::cout << "----------------------------------------------\n";
    
    // Iterate over all fields in the order
    for (auto& element : jsonData["result"]["order"].items()) {
        
        // Format timestamps in the order details
        if (element.key() == "last_update_timestamp" || element.key() == "creation_timestamp")
            std::cout << std::left << std::setw(30) << element.key() << ": " << FormatTimestamp(element.value()) << "\n";
        else
            std::cout << std::left << std::setw(30) << element.key() << ": " << element.value() << "\n";
    }
    
    std::cout << "\n";
}

void
Primitves::PrintOrderBook (String & pResponse)
{
        Json jsonData;

    jsonData = Json::parse (pResponse);
    
    std::cout << "Order Book:\n";
    
    std::cout << "----------------------------------------------\n";
    
    // Print general information with formatted timestamp
    std::cout << std::left << std::setw(30) << "Timestamp:" << FormatTimestamp(jsonData["result"]["timestamp"]) << "\n";
    std::cout << std::left << std::setw(30) << "State:" << jsonData["result"]["state"] << "\n";
    std::cout << std::left << std::setw(30) << "Instrument Name:" << jsonData["result"]["instrument_name"] << "\n";
    std::cout << std::left << std::setw(30) << "Last Price:" << jsonData["result"]["last_price"] << "\n";
    std::cout << std::left << std::setw(30) << "Best Bid Price:" << jsonData["result"]["best_bid_price"] << "\n";
    std::cout << std::left << std::setw(30) << "Best Bid Amount:" << jsonData["result"]["best_bid_amount"] << "\n";
    std::cout << std::left << std::setw(30) << "Best Ask Price:" << jsonData["result"]["best_ask_price"] << "\n";
    std::cout << std::left << std::setw(30) << "Best Ask Amount:" << jsonData["result"]["best_ask_amount"] << "\n";
    
    // Print bids in tabular format
    std::cout << "\nBids:\n";
    std::cout << std::left << std::setw(15) << "Price" << std::setw(20) << "Amount" << "\n";
    std::cout << "-----------------------------------------\n";
    for (const auto& bid : jsonData["result"]["bids"]) {
        
        std::cout << std::left << std::setw(15) << bid[0] << std::setw(10) << " "<< bid[1] << "\n";
    }
    
    std::cout << "-----------------------------------------\n\n";
}

void
Primitves::PrintCurrentPosition(String & pResponse)
{
        Json jsonData;

    jsonData = Json::parse (pResponse);
    
    std::cout << "Current Positions\n";
    
    std::cout << "----------------------------------------------\n";
    
    // Iterate over all fields in the first element of "result"
    for (auto& element : jsonData["result"][0].items()) {
        
        // Format timestamps in the account info
        if (element.key() == "usIn" || element.key() == "usOut")
            std::cout << std::left << std::setw(30) << element.key() << ": " << FormatTimestamp(element.value()) << "\n";
        else
            std::cout << std::left << std::setw(30) << element.key() << ": " << element.value() << "\n";
    }
    
    std::cout << "\n";
}

void
Primitves::PrintCancelOrderCount (String & pResponse)
{
        Json jsonData;

    jsonData = Json::parse (pResponse);
    
    std::cout << "Simple Value:\n";
    
    std::cout << "----------------------------------------------\n";
    
    // Directly print the result value
    std::cout << std::left << std::setw(30) << "Result:" << jsonData["result"] << "\n\n";
}

void
Primitves::PrintCancelOrderDetail (String & pResponse)
{
        Json jsonData;

    jsonData = Json::parse (pResponse);
    
    std::cout << "Cancelled Order Details:\n";
    
    std::cout << "----------------------------------------------\n";
    
    // Iterate over all fields in the order
    for (auto& element : jsonData["result"].items()) {
        
        // Format timestamps in the order details
        if (element.key() == "last_update_timestamp" || element.key() == "creation_timestamp")
            std::cout << std::left << std::setw(30) << element.key() << ": " << FormatTimestamp(element.value()) << "\n";
        else
            std::cout << std::left << std::setw(30) << element.key() << ": " << element.value() << "\n";
    }
    
    std::cout << "\n";
}

bool
Primitves::CheckResponse (String & pResponse)
{
        Json jsonData;
    
    jsonData = Json::parse (pResponse);
    
    if (jsonData.contains("error")) {
        
        std::cout << "API Error: \n" <<  jsonData["error"]["message"];
        return true;
    }
    
    return false;
}

String
Primitves::FormatTimestamp (long long pTimestamp)
{
        char buffer[100];
    
    // Convert milliseconds to seconds
    Clock::time_point tp = Clock::time_point (std::chrono::milliseconds (pTimestamp));
    
    std::time_t time = Clock::to_time_t (tp);
    std::tm *utc_tm = std::gmtime(&time); // Convert to UTC
    
    
    std::strftime (buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", utc_tm);
    
    return String (buffer) + " UTC";
}
