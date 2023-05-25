//code taken from assignment 1 template

#ifndef HELPER_H
#define HELPER_H
#include "Coin.h"
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>

class Helper
{
private:
    Helper();

public:

    /**
     * @brief Check whether the given string is an integer or a float 
     * 
     * @param s The given string
     * @return true if the string is an integer or a float 
     * @return false if the string is neither an integer nor a float 
     */
    static bool isNumber(std::string s);

    /**
     * @brief Split the given string given a delimeter. For instance, given the string "1,2,3" and the delimeter ",", 
     *        This string will be splited into "1","2","3", and they will be put into the vector.  
     * 
     * @param s The given string
     * @param tokens The vector containing the results
     * @param delimeter the string based on which splitting is performed
     */
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    /**
     * @brief Read the user input (a line) from keyboard
     * 
     * @return the user input.
     */
    static std::string readInput();

    static void printInvalidInput();
    static std::string strip(std::string s);
    static int str_to_int(std::string s);
    static std::string generate_ID(int id_num);
    static int strip_ID(std::string id);
    // static std::string cents_to_dollars(unsigned cents);
    /*
        since the isNumber does not work as expected... i have created a sort of temporary fix
        it really just checks whether the input was a whole number or not
        
    */
    static bool do_change(int cents, std::vector<Coin*>till);
    static bool is_int(std::string s);
    static bool is_valid_denom(unsigned x);
    static int get_index_for_denom(unsigned x);
};
#endif