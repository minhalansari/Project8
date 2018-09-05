// project 8 - market struct constructor and 2 functions
//first constructor opens file and reads it and then stores the data in a map
//function get_price takes a stock name and a date and checks if the values entered are valid then goes into map to get the price of specified stock on specified date
//function high_low_year gives the highet and lowest price in a year

#include <iostream>
#include "proj08_market.h"
#include <fstream>
using std::ifstream;
#include <string>
using std::string; 
#include <sstream>
using std::istringstream;
#include<map>
using std::map;
#include<vector>
using std::vector;
#include<utility>
using std::pair; using std::make_pair;


Market::Market(string file_name){
    //initialize values
    long date;
    double num;
    string line;
    ifstream inFile; //open file
    inFile.open(file_name);
    while(getline(inFile, line )){ //read file line by line
        istringstream iss(line); //separate first word in line as date
        iss >> date;
        for(int i=0; i<31; i++){ //store the rest of the words as values in the map
            iss>> num;
            stocks[date].push_back(num);
        }
    }

    
}

double Market::get_price(string stock, long date) const {
    double not_valid = -1.0; //to return if not valid stock name or date
    if (std::find(symbol_list.begin(), symbol_list.end(), stock) != symbol_list.end()){ //check if stock name exists in list
        if ( stocks.find(date) == stocks.end() ) { //check if date exists in stock
            return not_valid;
        } 
        else {
            std::ptrdiff_t pos  = distance(symbol_list.begin(), find(symbol_list.begin(), symbol_list.end(), stock)); //get index of stock
            return stocks.at(date)[pos]; //get value
        }
    }
    else{
        return not_valid;
    }
}

pair<double, double> Market::high_low_year(long year, string symbol){
    pair<double, double> p1;
    double largest = -1000000; //initialize small and large numbers 
    double smallest = 1000000;
    for(map<long,vector<double>>::iterator it = stocks.begin(); it != stocks.end(); ++it) { //go through map
        if(it->first/10000 == year){ //go through keys for that year
            double price = get_price(symbol, it->first); //get price then check if it is smallest or largesst
            if(price > largest){
                largest = price;
            }
            if(price < smallest){
                smallest = price;
            }
        }
        
        
    }
    if(largest == -1000000 and smallest == 1000000){ //for errors
        largest = -1.0;
        smallest = -1.0;
    }
    p1 = make_pair(largest, smallest); //make pair of smallest and largest
    return p1;
}
    



