#pragma once

#include <vector>
#include <limits>
#include <math.h>
#include "OrderBookEntry.h"
#include "OrderBook.h"

// Structure for Advisorbot header adapted from Merklerex class in example code 
class Advisorbot
{
    public:
        Advisorbot();
        /** Call this to start the sim */
        void init();
    private: 
        // Advisorbot commands (capabilities)
        void help();
        void helpcmd();
        void prod();
        void min();
        void max(); 
        void avg();
        void predict();
        void time();
        void step();
        void standardDev(); 

        // Functionas and variables defined here to make them available outside local functions
        std::string getCommand();
        void processCommand(std::string);
        std::string currentTime;
        std::string command; 

	OrderBook orderBook{"20200317.csv"};
       



};
