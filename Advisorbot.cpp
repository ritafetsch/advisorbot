#include <iostream>
#include <vector>
#include "Advisorbot.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"

/** Advisorbot constructor */
Advisorbot::Advisorbot() {
    
}

/** Starts the Advisorbot Sim -- Structure for init adapted from example code (Merklerex sim) */
void Advisorbot::init()
{
    std::string advisorInput;
    currentTime = orderBook.getEarliestTime();

    while(true){
        advisorInput = getCommand();
        processCommand(advisorInput);
    }
}

/** Purpose: list all available commands */
void Advisorbot::help(){    
    std::cout << "advisorbot>    The available commands are: help, help>cmd, prod, min, max, avg, predict, time, step, and standardDev" << std::endl;
}

/** Purpose: output help for the specified command */
void Advisorbot::helpcmd(){
    
    std::string helpOption;
    do {
        // Identifies available help options for user 
        std::cout << "advisorbot>    Identify the command you want help with. Pick one of: 'prod', 'min', 'max', 'avg', 'predict', 'time', 'step', and 'standardDev' " << std::endl;
        std::cout << "advisorbot>    (Enter 'exit' if you wish to return to the main menu) " << std::endl;

        std::cin >> helpOption;

        // Handles invalid user input 
        if (helpOption != "prod" && helpOption != "min" && helpOption != "max" && helpOption != "avg" && helpOption != "predict" && helpOption != "time" && helpOption != "step" && helpOption != "standardDev") {
            std::cout << "Invalid input! Please enter one of: 'prod', 'min', 'max', 'avg', 'predict', 'time', 'step', or 'standardDev' " << std::endl;
        }


        if (helpOption == "prod"){
        std::cout << "advisorbot>    Selecting 'prod' will list all available products. "<<   std::endl;
        }
        if (helpOption == "min"){
            std::cout << "advisorbot>    Selecting 'min' will find the minimum bid or ask for a product in the current time step "<<   std::endl;
        }
        if (helpOption == "max"){
            std::cout << "advisorbot>    Selecting 'max' will find the maximum bid or ask for a product in the current time step "<<   std::endl;
        }
        if (helpOption == "avg"){
            std::cout << "advisorbot>    Selecting 'avg' will compute the average ask or bid for the sent product over the sent number of time steps"<<   std::endl;
        }
        if (helpOption == "predict"){
            std::cout << "advisorbot>    Selecting 'predict' will predict the max/min ask/bid of the sent product for the next time step" <<   std::endl;
        }
        if (helpOption == "time"){
            std::cout << "advisorbot>    Selecting 'time' will state the current time in the dataset, i.e. which timeframe are we looking at "<<   std::endl;
        }
        if (helpOption == "step"){
            std::cout << "advisorbot>    Selecting 'step' will allow you to move to next time step "<<   std::endl;
        }
        if (helpOption == "standardDev"){
            std::cout << "advisorbot>    Selecting 'standardDev' will allow you to calculate the standard deviation for the sent product and type over all timestamps from current time."<<   std::endl;
        }
        // Creating space for aesthetics
        for (unsigned int i = 0; i < 4; ++i) {std::cout << " " << std::endl;}

    } while (helpOption != "exit"); 

}

/** Purpose: list available products -- code copied and adapted from starter code */
void Advisorbot::prod(){
    std::cout << "advisorbot>    List of available products: " << std::endl;
    // Code taken from example code (Merklerex sim)
    for (std::string const& p : orderBook.getKnownProducts()){
        std::cout << "Product: " << p << std::endl;
    }
    // Creating space for aesthetics
    for (unsigned int i = 0; i < 2; ++i) {std::cout << " " << std::endl;}
}

/** Purpose: find minimum bid or ask for product in current time step */
void Advisorbot::min(){
    
    // Collects user input on prompt and tokenises it into a vector of strings
    // Method of getting user input adapted from example code 
    std::cout << "advisorbot>    Find the minimum bid or ask for a product in the current time step. Please specify product and type: e.g. ETH/BTC,ask" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    // Check if user input is valid
    if ( (tokens.size() != 2 )   ||    (tokens[0] !=  "BTC/USDT"  && tokens[0] !=  "DOGE/BTC" && tokens[0] !=  "DOGE/USDT" && tokens[0] !=  "ETH/BTC" && tokens[0] !=  "ETH/USDT" ) || (tokens[1] !=  "bid"  && tokens[1] !=  "ask" )  ) 
    {
        std::cout << "advisorbot>    Invalid input! Please specify product and type in this way: e.g. ETH/BTC,ask" << std::endl;
    }       

    // Good input 
    else {
        // Convert tokenised input values in order to make calculations for min price and inform user what they have selected / what results will be filtered to
        std::string requested_currency = tokens[0];
        std::string requested_type = tokens[1];
        std::cout <<   ""      << std::endl;
        std::cout << "advisorbot>    You requested the minimum " << requested_type << " for: " << requested_currency << std::endl;
    
       
        // Get orders in current timestamp with sent product and type
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& product : orderBook.getKnownProducts()){
            std::vector<OrderBookEntry> entries = orderBook.getOrders(
                                                                    OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                    product, 
                                                                    currentTime);
            // Calculate min price of entries for sent product and type
            if (product == requested_currency){
                std::cout << "advisorbot>    Min " << requested_type << " for " << requested_currency << ": " << OrderBook::getLowPrice(entries) << std::endl;
                
            }
        }

    }
    // Creating space for aesthetics
    for (unsigned int i = 0; i < 2; ++i) {std::cout << " " << std::endl;}   
    
}

/** Purpose: find maximum bid or ask for product in current time step */
void Advisorbot::max(){

    // Collects user input on prompt and tokenises it into a vector of strings
    // Method of getting user input adapted from example code 
    std::cout << "advisorbot>    Find the maximum bid or ask for a product in the current time step. Please specify product and type: e.g. ETH/BTC,ask" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    
    // Check if user input is valid
    if ( (tokens.size() != 2 )   ||    (tokens[0] !=  "BTC/USDT"  && tokens[0] !=  "DOGE/BTC" && tokens[0] !=  "DOGE/USDT" && tokens[0] !=  "ETH/BTC" && tokens[0] !=  "ETH/USDT" ) || (tokens[1] !=  "bid"  && tokens[1] !=  "ask" )  ) 
    {
        std::cout << "advisorbot>    Invalid input! Please specify product and type in this way: e.g. ETH/BTC,ask" << std::endl;
        
    }
    
    // Good input 
    else {
        // Convert tokenised input values in order to make calculations for max price and inform user what they have selected / what results will be filtered to
        std::string requested_currency = tokens[0];
        std::string requested_type = tokens[1];
        std::cout <<   ""      << std::endl;
        std::cout << "advisorbot>    You requested the maximum " << requested_type << " for: " << requested_currency << std::endl;

        // Get orders in current timestamp with sent product and type
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& product : orderBook.getKnownProducts()){
            std::vector<OrderBookEntry> entries = orderBook.getOrders(
                                                                        OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                        product, 
                                                                        currentTime);
            // Calculate max price of entries for sent product and type 
            if (product == requested_currency){
                std::cout << "advisorbot>    Max " << requested_type << " for " << requested_currency << ": " << OrderBook::getHighPrice(entries) << std::endl;

            }
        }
    }
    
} 

/** Purpose: compute average ask or bid for the sent product over the sent number of time steps. */
void Advisorbot::avg(){ 
    unsigned int spread;

    // Collects user input on prompt and tokenises it into a vector of strings
    // Method of getting user input adapted from example code 
    std::cout << "advisorbot>    Avg will compute the average ask or bid for specified product over specified number of time steps. Please specify product, type, and number of timesteps: e.g. ETH/BTC,ask,10" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    // Check if user input is valid
    if (tokens.size() != 3  ||    (tokens[0] !=  "BTC/USDT"  && tokens[0] !=  "DOGE/BTC" && tokens[0] !=  "DOGE/USDT" && tokens[0] !=  "ETH/BTC" && tokens[0] !=  "ETH/USDT" ) || (tokens[1] !=  "bid"  && tokens[1] !=  "ask" )  )
    {
        std::cout << "advisorbot>    Invalid input! Please specify product,type, and timesteps in this way: e.g. ETH/BTC,ask,10" << std::endl;
    }
    
    else {
        // Convert tokenised input values in order to make calculations for avg price and inform user what they have selected / what results will be filtered to
        std::string requested_product = tokens[0];
        std::string requested_type = tokens[1];
        // Covert user input for number of timestamps to int. If input no convertable, value is set to 0 and handled 
        try {
            spread = std::stoi(tokens[2]);
        } catch (std::exception& e) {
            spread = 0;
        }
        if (spread == 0) {
            std::cout << "advisorbot>    Bad input for number of time steps!" << std::endl;
        }

        // Good input 
        else{
            std::cout <<   ""      << std::endl;
            std::cout << "advisorbot>    You requested the average " << requested_type << " price for: " << requested_product << " over the last " << spread << " time steps." << std::endl; 

            // get orders with sent filters for product, type, and number of timestamps average price will be calculated over 
            // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
            for (std::string const& timestamp: orderBook.getKnownTimestamps()){
            std::vector<OrderBookEntry> entries = orderBook.getOrders(
                                                                        OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                        requested_product, 
                                                                        currentTime);
            // Perform caclulation for average price on orders produced via sent filters
            std::cout << "advisorbot>    Current time is: " << entries[0].timestamp << std:: endl;
            std::cout <<   ""      << std::endl;
            std::cout << "advisorbot>   The average " << requested_type << " price for: " << requested_product << " over the last " << spread << " time steps is: "<< OrderBook::getAvgPrice(entries,spread) << std::endl;
            break;

            }
        }
    }
}

/** Purpose: predict max or min ask or bid for the sent product for the next time step */
void Advisorbot::predict(){
    // Declaring Local variables
    double sma, smoothing, initialEMA, previousEMA, currentEMA, initialEmaMax, previousEmaMax, currentEmaMax;
    std::string previousEmaTimestamp,input;
    std::vector<std::string> gettingPreviousTime;
    
    // Collects user input on prompt and tokenises it into a vector of strings
    // Method of getting user input adapted from example code 
    std::cout << "advisorbot>    Predict will predict max or min ask or bid for the specified product for the next time step. Please specify max or min, product, and type: e.g. min,ETH/BTC,ask" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    // Check if user input is valid 
    if (tokens.size() != 3  ||  (tokens[0] !=  "min"  && tokens[0] !=  "max" )  ||  (tokens[1] !=  "BTC/USDT"  && tokens[1] !=  "DOGE/BTC" && tokens[1] !=  "DOGE/USDT" && tokens[1] !=  "ETH/BTC" && tokens[1] !=  "ETH/USDT" ) || (tokens[2] !=  "bid"  && tokens[2] !=  "ask" )  ){
        std::cout << "advisorbot>    Invalid input! Please specify product,type, and timesteps in this way: e.g. min,ETH/BTC,ask" << std::endl;
    }
    // If good input: 
    else {
        
        // Convert tokenised input values in order to make calculations for cost predictions and inform user what they have selected / what results will be filtered to
        std::string requested_maxmin = tokens[0];
        std::string requested_product = tokens[1];
        std::string requested_type = tokens[2];
        std::cout <<   ""      << std::endl;
        std::cout << "advisorbot>    You requested the predicted " << requested_maxmin << " " << requested_type << " price for: " << requested_product << " in the next timestamp." << std::endl; 


        /** Calculating SMA (Simple Moving Average) for earliest timestamp of entries with sent filter */
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& timestamp: orderBook.getKnownTimestamps()){
            std::vector<OrderBookEntry> smaCalc = orderBook.getOrders(
                                                                        OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                        requested_product, 
                                                                        orderBook.getEarliestTime());
            // Call to getSMA function from orderbook which calculates simple moving average for earliest timestamp
            sma = OrderBook::getSMA(smaCalc);
            break;
        }

        
        /** Obtaining previous timestamp so we can use it to calculate previous timestamps EMA */
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& timestamp: orderBook.getKnownTimestamps()){
            std::vector<OrderBookEntry> entries = orderBook.getOrders(
                                                                            OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                            requested_product, 
                                                                            timestamp);
             /** Calculating smoothing using all timestamps from the beginning till the current timestamp */
            smoothing = 2.0 / (entries.size() + 1.0);
            if (timestamp == currentTime) {
                break;
            }
            else {
                gettingPreviousTime.push_back(timestamp);
                previousEmaTimestamp = gettingPreviousTime[gettingPreviousTime.size() -1];
            }
        }
        // Handles case where current time is earliest timestamp and thus where decrementing one time stamp results in null
        if (previousEmaTimestamp == "") {
            previousEmaTimestamp = currentTime;
        }

        /** Iterate over all products with specified filters dpeending on calculation needed -- one path for min, one path for max */    
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& timestamp: orderBook.getKnownTimestamps()){

            if (requested_maxmin == "min") {

                /** first timestamp EMA (Exponential Moving Average) of min price -- calculating EMA for first timestamp uses SMA as previous day's EMA */
                std::vector<OrderBookEntry> initialEmaEntriesMin = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                orderBook.getEarliestTime());
                double initialMin = OrderBook::getLowPrice(initialEmaEntriesMin);
                initialEMA = (initialMin - sma)   *   smoothing + sma ;

                /** previous EMA - min */
                std::vector<OrderBookEntry> previousEmaEntriesMin = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                previousEmaTimestamp);
                double previousMin = OrderBook::getLowPrice(previousEmaEntriesMin);
                previousEMA = (previousMin - initialEMA)   *   smoothing + initialEMA ;
            
                /** current EMA - min */
                std::vector<OrderBookEntry> currentEmaEntriesMin = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                currentTime);
                double currentMin = OrderBook::getLowPrice(currentEmaEntriesMin);
                currentEMA = (currentMin - previousEMA)   *   smoothing + previousEMA ;
                
                // console output w result
                std::cout << "advisorbot>    Current time: " << currentTime << std:: endl;
                std::cout << "advisorbot>    EMA calculated for min price of " << requested_product << " in intial timestamp (using SMA): " << initialEMA <<  std::endl;
                std::cout << "advisorbot>    EMA calculated for min price of " << requested_product << " in previous timestamp (using previous EMA): " << previousEMA <<  std::endl;

                std::cout <<   ""      << std::endl;
                std::cout << "advisorbot>    The predicted min " << requested_type << " price for " << requested_product << " in the next time step is: " << currentEMA << std:: endl;
                break;
            }
                
            if (requested_maxmin == "max") {

                /** first timestamp EMA (Exponential Moving Average) of max price -- calculating EMA for first timestamp uses SMA as previous day's EMA */
                // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
                std::vector<OrderBookEntry> initialEmaEntriesMax = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                orderBook.getEarliestTime());

                double initialMax = OrderBook::getHighPrice(initialEmaEntriesMax);
                initialEmaMax = (initialMax - sma)   *   smoothing + sma ;
            
                /** previous EMA - max */
                std::vector<OrderBookEntry> previousEmaEntriesMax = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                previousEmaTimestamp);
            
                double previousMax = OrderBook::getHighPrice(previousEmaEntriesMax);
                previousEmaMax = (previousMax - initialEmaMax)   *   smoothing + initialEmaMax ;
            
                /** current EMA - max*/
                std::vector<OrderBookEntry> currentEmaEntriesMax = orderBook.getOrders(
                                                                                OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                                requested_product, 
                                                                                currentTime);
                double currentMax = OrderBook::getHighPrice(currentEmaEntriesMax);
                currentEmaMax = (currentMax - previousEmaMax)   *   smoothing + previousEmaMax ;

                // Conosle output w result 
                std::cout << "advisorbot>    Current time: " << currentTime << std:: endl;
                std::cout << "advisorbot>    EMA calculated for max price of " << requested_product << " in intial timestamp (using SMA): " << initialEmaMax <<  std::endl;
                std::cout << "advisorbot>    EMA calculated for max price of " << requested_product << " in previous timestamp (using previous EMA): " << previousEmaMax <<  std::endl;

                std::cout <<   ""      << std::endl;
                std::cout << "advisorbot>    The predicted max " << requested_type << " price for " << requested_product << " in the next time step is: " << currentEmaMax << std:: endl;
                break;
            }
        }
    }    
    
    for (unsigned int i = 0; i < 4; i++) {std::cout << " " << std::endl;}  
}

/**  Purpose: state current time in dataset, i.e. which timeframe are we looking at */
// Time function copied from example code and adapted for Advisorbot
void Advisorbot::time(){
    std::cout <<  "advisorbot>    Current time is: " <<  currentTime <<    std::endl;
    for (unsigned int i = 0; i < 4; i++) {std::cout << " " << std::endl;}
}

/**  Purpose: move to next time step */
// Step function copied from example code and adapted for Advisorbot
void Advisorbot::step()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout <<  "advisorbot>    Moved to next time step. Time is now: " <<  currentTime <<    std::endl;

}

/**  Purpose: Calculates Standard Deviation of sent prices for sent product and type in current timestamp */
void Advisorbot::standardDev(){
    double mean,sumDeviations,standardDev;
    
    // Collects user input on prompt and tokenises it into a vector of strings
    // Method of getting user input adapted from example code 
    std::cout << "advisorbot>    standardDev will calculate the standard deviation of sent product/type in current timestamp. Please specify product, and type: e.g. ETH/BTC,ask" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    // Check if user input is valid  
    if ( (tokens.size() != 2)    ||  (tokens[0] !=  "BTC/USDT"  && tokens[0] !=  "DOGE/BTC" && tokens[0] !=  "DOGE/USDT" && tokens[0] !=  "ETH/BTC" && tokens[0] !=  "ETH/USDT" ) || (tokens[1] !=  "bid"  && tokens[1] !=  "ask" )                  ) {
        std::cout << "advisorbot>    Invalid input! Please specify product and type in this way: e.g. ETH/BTC,ask" << std::endl;
    }
    
    // If good input: 
    else {
        // Convert tokenised input values in order to make calculations for standard deviation and inform user what they have selected / what results will be filtered to
        std::string requested_product = tokens[0];
        std::string requested_type = tokens[1];
        std::cout <<   ""      << std::endl;
        std::cout << "advisorbot>    You requested the average " << requested_type << " price for: " << requested_product << " in the next timestamp." << std::endl; 


        // get orders with sent filters for product and type in the current timestamp 
        // Method of obtaining orders according to user input, use of orderbook, and call to getKnownTimestamps and get Orders functions adapted from example code
        for (std::string const& timestamp: orderBook.getKnownTimestamps()){

            std::vector<OrderBookEntry> standardDevEntries = orderBook.getOrders(
                                                                        OrderBookEntry::stringToOrderBookType(requested_type), 
                                                                        requested_product, 
                                                                        currentTime);

            // Perform caclulation for standard deviaton on orders produced by sent filters via user input 
            double mean = OrderBook::getAvgPrice(standardDevEntries,standardDevEntries.size());

            for (unsigned int i = 0; i < standardDevEntries.size(); ++i){
                double distance;
                sumDeviations = 0.0;
                distance = standardDevEntries[i].price - mean;
                sumDeviations = sumDeviations + (distance * distance);
                standardDev = sqrt(sumDeviations / standardDevEntries.size())  ;
            }
            std::cout << "Standard Deviation for " << requested_type << " prices of " << requested_product << " in the current timestamp is: " <<  standardDev << std::endl;

            break;
        }
    }

} 

/**  Purpose: Obtains users choice of command to navigate through sim */
std::string Advisorbot::getCommand(){


    for (unsigned int i = 0; i < 2; i++) {std::cout << " " << std::endl;}
    std::cout << "advisorbot>    Please enter a command, or type 'help' for a list of commands." << std::endl;
    std::cin >> command;

    for (unsigned int i = 0; i < 4; i++) {std::cout << " " << std::endl;}
    std::cout << "advisorbot>    User input: " << command << std::endl;

    return command;
}

/**  Purpose: Executes specific sim functionality based on user's choice of command*/
void Advisorbot::processCommand(std::string command){ 
    // Handling invalid input
    if (command != "help" && command != "help>cmd" && command != "prod" && command != "min" && command != "max" && command != "avg" && command != "predict" && command != "time" && command != "step" && command != "standardDev") {
        std::cout << "Invalid input! Please enter a command, or type 'help' for a list of commands." << std::endl;
    }


    if (command == "help") {
        help();
    }
    if (command == "help>cmd") {
        helpcmd();
    }
    if (command == "prod") {
        prod();
    }
    if (command == "min") 
    {
        min();
    }
    if (command == "max") 
    {
        max();
    }
    if (command == "avg") 
    {
        avg();
    }       
    if (command == "predict") 
    {
        predict();
    }     
    if (command == "time") {
        time();
    }     
    if (command == "step") {
        step();
    } 
    if (command == "standardDev") {
        standardDev();
    } 

}
