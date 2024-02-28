#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

// Class adapted from example code - used some functions, deleted others, and wrote 
// my own - specifications of which are mine and which came from example code are in main OrderBook cpp file
class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all known products in the dataset*/
        std::vector<std::string> getKnownProducts();
        /** return vector of all known timestamps in the dataset*/

        std::vector<std::string> getKnownTimestamps();
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);

        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        
        std::string getNextTime(std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);

        static double getAvgPrice(std::vector<OrderBookEntry>& orders,int amount);
        static double getSMA(std::vector<OrderBookEntry>& orders);
        static double getSmoothing(std::vector<OrderBookEntry>& orders);
       

    private:
        std::vector<OrderBookEntry> orders;


};
