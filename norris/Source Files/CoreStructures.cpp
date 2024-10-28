#include "CoreStructures.hpp"

template<>
String
CoreStructures::label (eContractType pValue)
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
CoreStructures::label (eCurrencyType pValue)
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
CoreStructures::label (eOrderType pValue)
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
CoreStructures::label (eValidity pValue)
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
CoreStructures::label (eDirection pValue)
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
CoreStructures::PrintBuyOrderDetails(String & pResponse)
{
    Json data;
    Json order;
    
    data = Json::parse (pResponse);
    
    order = data["result"]["order"];
    
    std::cout << "------- Placed Order ------- " << "\n";
    
    std::cout << "Order Details:\n";
    std::cout << std::left
    << std::setw(16) << "Order ID"
    << std::setw(12) << "Order Type"
    << std::setw(10) << "State"
    << std::setw(10) << "Price"
    << std::setw(12) << "Filled Amt"
    << std::setw(12) << "Avg Price"
    << std::setw(10) << "Direction"
    << std::setw(16) << "Instrument"
    << std::setw(20) << "Timestamp"
    << std::endl;
    
    std::cout << std::left
    << std::setw(16) << order.value("order_id", "N/A")
    << std::setw(12) << order.value("order_type", "N/A")
    << std::setw(10) << order.value("order_state", "N/A")
    << std::setw(10) << order.value("price", 0.0)
    << std::setw(12) << order.value("filled_amount", 0)
    << std::setw(12) << order.value("average_price", 0.0)
    << std::setw(10) << order.value("direction", "N/A")
    << std::setw(16) << order.value("instrument_name", "N/A")
    << std::setw(20) << order.value("creation_timestamp", 0)
    << std::endl;
}

void
CoreStructures::PrintOrderBook(String & pResponse)
{
    
        Json data;
        Json result;
        Json bids;
    
    data = Json::parse (pResponse);
    
    result = data["result"];
    bids   = result["bids"];
    
    std::cout << "Main Order Details:\n";
    std::cout << std::left
    << std::setw(20) << "Instrument Name"
    << std::setw(15) << "State"
    << std::setw(15) << "Settle Price"
    << std::setw(15) << "Open Interest"
    << std::setw(15) << "Min Price"
    << std::setw(15) << "Max Price"
    << std::setw(15) << "Mark Price"
    << std::setw(15) << "Last Price"
    << std::setw(15) << "Index Price"
    << std::setw(15) << "Funding 8H"
    << std::setw(15) << "Current Fund"
    << std::setw(15) << "Change ID"
    << std::endl;
    
    std::cout << std::left
    << std::setw(20) << result.value("instrument_name", "N/A")
    << std::setw(15) << result.value("state", "N/A")
    << std::setw(15) << result.value("settlement_price", 0.0)
    << std::setw(15) << result.value("open_interest", 0.0)
    << std::setw(15) << result.value("min_price", 0.0)
    << std::setw(15) << result.value("max_price", 0.0)
    << std::setw(15) << result.value("mark_price", 0.0)
    << std::setw(15) << result.value("last_price", 0.0)
    << std::setw(15) << result.value("index_price", 0.0)
    << std::setw(15) << result.value("funding_8h", 0.0)
    << std::setw(15) << result.value("current_funding", 0.0)
    << std::setw(15) << result.value("change_id", 0)
    << std::endl;
    
    std::cout << "\nBid Details:\n";
    std::cout << std::left
    << std::setw(15) << "Bid Price"
    << std::setw(15) << "Bid Amount"
    << std::endl;
    
    for (const auto& bid : bids) {
        
        if (bid.size() >= 2) {
            
            std::cout << std::left
            << std::setw(15) << bid[0].get<double>()  // Bid price
            << std::setw(15) << bid[1].get<double>()  // Bid amount
            << std::endl;
        }
    }
}

void
CoreStructures::PrintCurrentPosition (String & pResponse)
{
        Json data;
        Json position;
    
    data = Json::parse (pResponse);
    
    position = data["result"];
    
    std::cout << "Position Details:\n";
    std::cout << std::left
    << std::setw(15) << "Instrument"
    << std::setw(10) << "Kind"
    << std::setw(10) << "Direction"
    << std::setw(15) << "Avg Price"
    << std::setw(10) << "Leverage"
    << std::setw(15) << "Index Price"
    << std::setw(15) << "Mark Price"
    << std::setw(15) << "Settle Price"
    << std::setw(15) << "Size"
    << std::setw(15) << "Size Curr"
    << std::setw(15) << "Init Margin"
    << std::setw(20) << "Maint Margin"
    << std::setw(15) << "Float P&L"
    << std::setw(15) << "Total P&L"
    << std::setw(15) << "Realized P&L"
    << std::setw(15) << "Realized Fund"
    << std::setw(20) << "Est Liquid Price"
    << std::setw(20) << "Open Ord Margin"
    << std::setw(20) << "Interest Value"
    << std::endl;
    
    std::cout << std::left
    << std::setw(15) << position.value("instrument_name", "N/A")
    << std::setw(10) << position.value("kind", "N/A")
    << std::setw(10) << position.value("direction", "N/A")
    << std::setw(15) << position.value("average_price", 0.0)
    << std::setw(10) << position.value("leverage", 0)
    << std::setw(15) << position.value("index_price", 0.0)
    << std::setw(15) << position.value("mark_price", 0.0)
    << std::setw(15) << position.value("settlement_price", 0.0)
    << std::setw(15) << position.value("size", 0)
    << std::setw(15) << position.value("size_currency", 0.0)
    << std::setw(15) << position.value("initial_margin", 0.0)
    << std::setw(20) << position.value("maintenance_margin", 0.0)
    << std::setw(15) << position.value("floating_profit_loss", 0.0)
    << std::setw(15) << position.value("total_profit_loss", 0.0)
    << std::setw(15) << position.value("realized_profit_loss", 0.0)
    << std::setw(15) << position.value("realized_funding", 0.0)
    << std::setw(20) << position.value("estimated_liquidation_price", 0.0)
    << std::setw(20) << position.value("open_orders_margin", 0.0)
    << std::setw(20) << position.value("interest_value", 0.0)
    << std::endl;
}

void
CoreStructures::PrintOpenPositions (String & pResponse)
{
        Json data;
        Json result;
    
    data = Json::parse (pResponse);
    
    result = data["result"];
    
    std::cout << std::left
    << std::setw(15) << "Order ID"
    << std::setw(20) << "Order Type"
    << std::setw(15) << "State"
    << std::setw(10) << "Price"
    << std::setw(15) << "Filled Amt"
    << std::setw(15) << "Avg Price"
    << std::setw(10) << "Direction"
    << std::setw(25) << "Instrument"
    << std::setw(20) << "Timestamp"
    << std::setw(20) << "Time In Force"
    << std::setw(10) << "Reduce Only"
    << std::setw(10) << "Post Only"
    << std::setw(15) << "Max Show"
    << std::setw(10) << "API"
    << std::endl;
    
    
    for (Json order : result) {
        
        std::cout << std::left
        << std::setw(15) << order.value("order_id", "N/A")
        << std::setw(20) << order.value("order_type", "N/A")
        << std::setw(15) << order.value("order_state", "N/A")
        << std::setw(10) << order.value("price", 0.0)
        << std::setw(15) << order.value("filled_amount", 0)
        << std::setw(15) << order.value("average_price", 0.0)
        << std::setw(10) << order.value("direction", "N/A")
        << std::setw(25) << order.value("instrument_name", "N/A")
        << std::setw(20) << order.value("creation_timestamp", 0)
        << std::setw(20) << order.value("time_in_force", "N/A")
        << std::setw(10) << order.value("reduce_only", false)
        << std::setw(10) << order.value("post_only", false)
        << std::setw(15) << order.value("max_show", 0)
        << std::setw(10) << order.value("api", false)
        << std::endl;
    }
}
