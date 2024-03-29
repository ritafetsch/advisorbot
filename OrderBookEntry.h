#pragma once

#include <string>

// Entire OrderBookEntry Code adapted from example code (merklerex sim)
enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry
{
    public:
    

        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string username = "dataset");

        static OrderBookType stringToOrderBookType(std::string s);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};
