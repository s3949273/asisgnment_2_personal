#ifndef COIN_H
#define COIN_H
#include <iostream>
#include <vector>
// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS = 5, TEN_CENTS = 10, TWENTY_CENTS = 20, FIFTY_CENTS = 50, ONE_DOLLAR = 100, 
    TWO_DOLLARS = 200, FIVE_DOLLARS = 500, TEN_DOLLARS = 1000
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    Coin();
    Coin(Denomination denom, unsigned count);
    std::vector<Coin*> parse_coin_file(std::string filepath);
    void print();
    static Denomination unit_to_Denomination(unsigned x);
};

#endif // COIN_H
