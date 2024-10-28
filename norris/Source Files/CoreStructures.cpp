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
CoreStructures::PrintBuyOrderDetails (String & pResponse)
{
    Json data;
    Json order;
    
    data = Json::parse (pResponse);
    
    order = data["result"]["order"];
    
    printf("------- Placed Order -------\n");
    
    printf("Order Details:\n");
    printf("%-16s %-12s %-10s %-10s %-12s %-12s %-10s %-16s %-20s\n",
        "Order-ID", "Order-Type", "State", "Price",
        "Filled-Amt", "Avg-Price", "Direction",
        "Instrument", "Timestamp");

    printf("%-16s %-12s %-10s %-10.2f %-12d %-12.2f %-10s %-16s %-20d\n",
        order.value("order_id", "N/A").c_str(),
        order.value("order_type", "N/A").c_str(),
        order.value("order_state", "N/A").c_str(),
        order.value("price", 0.0),
        order.value("filled_amount", 0),
        order.value("average_price", 0.0),
        order.value("direction", "N/A").c_str(),
        order.value("instrument_name", "N/A").c_str(),
        order.value("creation_timestamp", 0));
}

void
CoreStructures::PrintOrderBook (String & pResponse)
{
    Json data;
    Json result;
    Json bids;
    
    data = Json::parse (pResponse);
    
    result = data["result"];
    bids   = result["bids"];
    
    printf("Main Order Details:\n");
    printf("%-20s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s %-15s\n",
        "Instrument-Name", "State", "Settle-Price", "Open-Interest",
        "Min-Price", "Max-Price", "Mark-Price",
        "Last-Price", "Index-Price", "Funding 8H",
        "Current-Fund", "Change-ID");

    printf("%-20s %-15s %-15.2f %-15.2f %-15.2f %-15.2f %-15.2f %-15.2f %-15.2f %-15.2f %-15.2f\n",
        result.value("instrument_name", "N/A").c_str(),
        result.value("state", "N/A").c_str(),
        result.value("settlement_price", 0.0),
        result.value("open_interest", 0.0),
        result.value("min_price", 0.0),
        result.value("max_price", 0.0),
        result.value("mark_price", 0.0),
        result.value("last_price", 0.0),
        result.value("index_price", 0.0),
        result.value("funding_8h", 0.0),
        result.value("current_funding", 0.0),
        result.value("change_id", 0));
    
    printf("\nBid Details:\n");
    printf("%-15s %-15s\n", "Bid Price", "Bid Amount");
    
    for (const auto& bid : bids) {
        if (bid.size() >= 2) {
            printf("%-15.2f %-15.2f\n", bid[0].get<double>(), bid[1].get<double>());
        }
    }
}

void
CoreStructures::PrintCurrentPosition(String & pResponse)
{
    Json data;
    Json position;
    
    data = Json::parse (pResponse);
    
    position = data["result"];
    
    printf("Position Details:\n");
    printf("%-15s %-10s %-10s %-15s %-10s %-15s %-15s %-15s %-15s %-15s %-20s %-15s %-15s %-15s %-15s %-20s %-20s %-20s\n",
        "Instrument", "Kind", "Direction", "Avg Price", "Leverage",
        "Index Price", "Mark Price", "Settle Price", "Size",
        "Size Curr", "Init Margin", "Maint Margin",
        "Float P&L", "Total P&L", "Realized P&L",
        "Realized Fund", "Est Liquid Price", "Open Ord Margin",
        "Interest Value");

    printf("%-15s %-10s %-10s %-15.2f %-10d %-15.2f %-15.2f %-15.2f %-15d %-15.2f %-15.2f %-20.2f %-15.2f %-15.2f %-15.2f %-15.2f %-20.2f %-20.2f %-20.2f\n",
        position.value("instrument_name", "N/A").c_str(),
        position.value("kind", "N/A").c_str(),
        position.value("direction", "N/A").c_str(),
        position.value("average_price", 0.0),
        position.value("leverage", 0),
        position.value("index_price", 0.0),
        position.value("mark_price", 0.0),
        position.value("settlement_price", 0.0),
        position.value("size", 0),
        position.value("size_currency", 0.0),
        position.value("initial_margin", 0.0),
        position.value("maintenance_margin", 0.0),
        position.value("floating_profit_loss", 0.0),
        position.value("total_profit_loss", 0.0),
        position.value("realized_profit_loss", 0.0),
        position.value("realized_funding", 0.0),
        position.value("estimated_liquidation_price", 0.0),
        position.value("open_orders_margin", 0.0),
        position.value("interest_value", 0.0));
}

void
CoreStructures::PrintOpenPositions(String & pResponse)
{
    Json data;
    Json result;
    
    data = Json::parse (pResponse);
    
    result = data["result"];
    
    printf("%-15s %-20s %-15s %-10s %-15s %-15s %-10s %-25s %-20s %-20s %-10s %-10s %-15s %-10s\n",
        "Order ID", "Order Type", "State", "Price", "Filled Amt",
        "Avg Price", "Direction", "Instrument", "Timestamp",
        "Time In Force", "Reduce Only", "Post Only", "Max Show", "API");

    for (Json order : result) {
        printf("%-15s %-20s %-15s %-10.2f %-15d %-15.2f %-10s %-25s %-20d %-20s %-10s %-10s %-15d %-10s\n",
            order.value("order_id", "N/A").c_str(),
            order.value("order_type", "N/A").c_str(),
            order.value("order_state", "N/A").c_str(),
            order.value("price", 0.0),
            order.value("filled_amount", 0),
            order.value("average_price", 0.0),
            order.value("direction", "N/A").c_str(),
            order.value("instrument_name", "N/A").c_str(),
            order.value("creation_timestamp", 0),
            order.value("time_in_force", "N/A").c_str(),
            order.value("reduce_only", false),
            order.value("post_only", false),
            order.value("max_show", 0),
            order.value("api", false));
    }
}
