#ifndef CASHREGISTER_H
#define CASHREGISTER_H
#define DEFAULT_COIN_COUNT 20
#include <iostream>
#include "Coin.h"
#include "helper.h"
#include <vector>

class CashRegister{

    public:
    std::vector<Coin*> coins;

    CashRegister();
    CashRegister(std::string filepath);
    ~CashRegister();
    
    void parse_coin_file(std::string filepath);
    void write_to_coin_file(std::string coinsfile);
    void display_coins();
    void reset_coin_count();
    bool do_change(int cents);    
    static int get_index_for_denom(unsigned x);
    int get_max_coin_value();
    private:
        int max_coin_value;
};


#endif