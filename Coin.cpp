#include "Coin.h"
#include <iostream>
#include "helper.h"
#include <fstream> 
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;

Coin::Coin(){}

Coin::Coin(Denomination denom, unsigned count){
    this->denom = denom;
    this->count = count;
}

void Coin::print(){
    std::cout << "Denomination: " << this->denom << std::endl;
    std::cout << "Count: " << this->count << std::endl; 
}

Denomination Coin::unit_to_Denomination(unsigned x){
    /*
        there's no need to make some overly complicated function using for loops or whatever
        when 8 if statements will do the trick
    */
    Denomination ret = Denomination(FIVE_CENTS);
    //we don't check for five cents because ret's default value is five cents
    if(x == 10){
        ret = TEN_CENTS;
    }else if(x == 20){
        ret = TWENTY_CENTS;
    }else if(x == 50){
        ret = FIFTY_CENTS;
    }else if(x == 100){
        ret = ONE_DOLLAR;
    }else if(x == 200){
        ret = TWO_DOLLARS;
    }else if(x == 500){
        ret = FIVE_DOLLARS;
    }else if(x == 1000){
        ret = TEN_DOLLARS;
    }  
    return ret;
}

std::vector<Coin*> Coin::parse_coin_file(string filepath){
    ifstream coins(filepath);
    string line_coins;
    vector<string> output_coins;
    std::vector<Coin*> ret(8);
    try{
        int counter = 0;
        while (getline(coins, line_coins)){
            Helper::splitString(line_coins, output_coins, ",");
            if (output_coins.size() > 2){
                string error_message = "too many attributes given to build coin object at line: "+std::to_string(counter+1);
                throw std::invalid_argument(error_message);
            }else{
                output_coins[0] = Helper::strip(output_coins.at(0));
                output_coins[1] = Helper::strip(output_coins.at(1));
                if(Helper::is_int(output_coins.at(0)) && Helper::is_int(output_coins.at(1))){
                    int denom = stoi(output_coins.at(0));
                    if(Helper::is_valid_denom(denom)){
                        ret[7-counter] = (new Coin(this->unit_to_Denomination(denom), stoi(output_coins.at(1))));
                    }else{
                        string error_message = "denomination given was not valid at line: "+std::to_string(counter+1);
                        throw std::invalid_argument(error_message);
                    }
                }else{
                    string error_message ="one of the argument of the coin object being built had either a ";
                    error_message += "decimal or a letter in it at line: "+ std::to_string(counter+1);
                    throw std::invalid_argument(error_message);
                }
            }
            counter ++;
        }
        coins.close();
    }
    catch(std::invalid_argument& e){
        cout<<e.what()<<endl;
    }
    return ret;
}