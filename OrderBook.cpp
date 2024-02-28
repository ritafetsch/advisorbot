#include <map>
#include <iostream>
#include "OrderBook.h"
#include "CSVReader.h"



/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

/** return vector of all know products in the dataset*/
// Function from example code (merklerex sim)
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    
    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}

/** return vector of all know products in the dataset*/
// Function based off getKnownProducts function from example code 
std::vector<std::string> OrderBook::getKnownTimestamps()
{
    std::vector<std::string> timestamps;

    std::map<std::string,bool> timestampMap;

    for (OrderBookEntry& e : orders)
    {
        timestampMap[e.timestamp] = true;
    }
    
    // now flatten the map to a vector of strings
    for (auto const& e : timestampMap)
    {
        timestamps.push_back(e.first);
    }

    return timestamps;
}


/** return vector of Orders according to the sent filters*/
// Function from example code (merklerex sim)
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, 
                                        std::string product, 
                                        std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && 
            e.product == product && 
            e.timestamp == timestamp )
            {
                orders_sub.push_back(e);
            }
    }
    return orders_sub;
}
// Function from example code (merklerex sim)
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max)max = e.price;
    }
    return max;
}
// My own function -- gets average price of orders sent over sent amount of time stamps
double OrderBook::getAvgPrice(std::vector<OrderBookEntry>& orders, int amount)
{

    double avgPrice;
    int lastIndex = orders.size();
    int firstIndex = orders.size() - amount ;

    for (int i = firstIndex; i < lastIndex; ++i){

        double sum = sum + orders[i].price;

        avgPrice = sum / amount;
        
    }
    return avgPrice;
}
// Function from example code (merklerex sim)
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min)min = e.price;
    }
    return min;
}

// My own function - calculates simple moving average of sent orders
double OrderBook::getSMA(std::vector<OrderBookEntry>& orders) {
    double sum;
    double sma;

    for (int i = 0; i < orders.size() ; ++i) {

        sum = sum + orders[i].price;
        sma = sum / orders.size();

    }
    return sma;
}

// My own function - calculates smoothing value for sma and ema calculations
double OrderBook::getSmoothing(std::vector<OrderBookEntry>& orders) {
    
    double size;
    double smoothing;

    size = orders.size();
    smoothing = 2 / (size + 1);
    
    return smoothing;
}

// Function from example code (merklerex sim)
std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

// Function from example code (merklerex sim)
std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp) 
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

