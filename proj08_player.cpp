//project 8 player struct functions
//four functions
//function buy takes the market ref a stock name a date and a quanitity and allows users to purchase the stock if they have the cash
//function sell takes same parameters as buy and allows users to sell a stock if they have the stock and the correct quantity
//function to_str returns a string of the cash a player has and all its map values of stock dates and quanities
//function combine creates a player that combines the cash value and stocks of two different platers 

#include <iostream>
#include "proj08_player.h"
#include "proj08_market.h"
#include <string>
using std::string;
#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<map>
#include<sstream>

bool Player::buy(Market &m, string stock, long date, long quantity){
    double price = m.get_price(stock, date); //get price of the stock on that day
    if(price == -1.0){ //if errors
        return false;
    }
    if(cash >= price * quantity){ //check if user has sufficient cash
        cash = cash - price * quantity; //update cash
        stocks[stock]= stocks[stock] + quantity; //update quantity
        return true;
           

      
    }
    else{
        return false; //if user doesnt have sufficient cash
    }
}

bool Player::sell(Market &m, string stock, long date, long quantity){
    double price = m.get_price(stock, date); //get price of stock on that date
    if(price == -1.0){ //if errors
        return false;
    }
    if ( stocks.find(stock) == stocks.end() ) { //check if user has the stock
        return false;
    } 
    else {
        if(stocks[stock] >= quantity){ //update cash and map if user has the stock
            cash = cash + price * quantity;
            stocks[stock] = stocks[stock] - quantity;
            return true;
        }
        else{
            return false;
        }
    }
   
}
string Player::to_str(){
    std::ostringstream strs; //change double to string
    strs.precision(2);
    strs<<std::fixed;
    strs << cash;
    std::string str_cash = strs.str();
//intialize values
    string output = "";
    string convrt = "";
    string result = "";
	for (auto it = stocks.cbegin(); it != stocks.cend(); it++) { //go through all map values and display as strings
	    convrt = std::to_string(it->second);
		output += (it->first) + ":" + (convrt) + ",";
	}
	
	result = output.substr(0, output.size() - 1 );
	
	return str_cash + "," + result;

    
    
}
Player Player::combine(Player& p2){
    double zero = 0; //zero value as double
    double newcash = cash + p2.cash; //cash of two users added together
    Player p3(newcash); //create new user and give the cash to it
    p3.stocks.insert(stocks.begin(), stocks.end()); //add stocks of both players to new players map 
    p3.stocks.insert(p2.stocks.begin(), p2.stocks.end());
    p2.cash = zero; //set old player values to zero and clear stock
    p2.stocks.clear();
    cash =  zero;
    stocks.clear();
    return p3;
}
