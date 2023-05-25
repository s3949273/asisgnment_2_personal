#include <stdlib.h>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main(){
    string TC_ID;

    cout << "Enter test case number: ";
    cin >> TC_ID;

    string cmd1;

    if (stoi(TC_ID) == 10) {
        cmd1 = "cp test_case/TC" + TC_ID + ".defaultcoins test_case/TC" + TC_ID + ".coins && cp test_case/default_test_case/TC.stock test_case/TC" + TC_ID + ".stock";
    } 
    else {
        cmd1 = "cp test_case/default_test_case/TC.coins test_case/TC" + TC_ID + ".coins && cp test_case/default_test_case/TC.stock test_case/TC" + TC_ID + ".stock";
    }
    string cmd2 = "./ppd test_case/TC" + TC_ID + ".stock test_case/TC" + TC_ID + ".coins < test_case/TC" + TC_ID + ".input > test_case/TC" + TC_ID + ".actual_ppd_out";
    string cmd3 = "diff -w test_case/TC" + TC_ID + ".output test_case/TC" + TC_ID + ".actual_ppd_out";
    string cmd4 = "diff -w -y test_case/TC" + TC_ID + ".coins test_case/TC" + TC_ID + ".expcoins";

    

    system(cmd1.c_str());
    system(cmd2.c_str());
    system(cmd3.c_str());
    system(cmd4.c_str());

}