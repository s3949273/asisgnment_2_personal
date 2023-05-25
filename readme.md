# What are the files which weren't given in the skeleton code:
>There are some files which we deemed necessary to help make the code a bit easier
to read. These files include:

>**CashRegister.cpp and Cashregister.h**
    This file and it's header are to manage  the  register which holds all of the 
    coins, initially we were going to use a vector of coins, but then deemed
    that it may be better functionality wise if we created its own class so that
    we could add related functions into it.

>**helper.cpp and helper.h**
    First of all this is not entirely our file, it was given in the Assignment 1 
    skeleton code, we realised that many of its functions related to user input would make our lives much easier, and as such we copy pasted it from our Assignmnent 1 and added some more functions, adjusted others to make it more relavent to the current project.

# What to run for the automated test
>As required by the specs, the ppd file contains the actual functioning code.
**The make file should be sufficient to make the the ppd exectuable.**
though we would recommend just running **`make clean`** just to be safe in case we have accidentally left some executables in there.
the command after that to run the executable created is:
`./ppd stock.dat coins.dat`
**and yes order is important**
this is because our code is expecting the stock file first and then the coins file. If it is not in this order, then the program will not be able to load the files correctly and abort.

>The given data files are the ones from the skeleton code, if you would like to restore them to their original value after running some tests you can use the following commands: 
for coins: 
        **`cp test_case/default_test_case/TC.coins coins.dat`**
    for stock:
        **`cp test_case/default_test_case/TC.stock stock.dat`**
    or all in one:  
        **`cp test_case/default_test_case/TC.coins coins.dat && cp test_case/default_test_case/TC.stock stock.dat`**



# What is the RunTestCase.cpp file?
>The RunTestCase.cpp file is used to run a particular test case which is inputted by the user, the following instructions provide more details.
>## Running the RunTestCase.cpp file
>The command to compile the file is: 
**`g++ -Wall -Werror -std=c++14 -O -o test Coin.cpp LinkedList.cpp Node.cpp Helper.cpp CashRegister.cpp RunTestCase.cpp`**
>runnng the file is a bit different from the main ppd file. Instead of giving it command line arguments, it will ask you for input inside. As such the command to run it will be: **`./RunTestCase`** 
given that you have compiled the file.
>note that the input has to be of a certain type.
>For example lets say you want to run test case 1,  then your input would be: 01 (note its not just "1") this is because the RunTestCase file is doing a direct string compare between your input and the test cases in the test_case folder. 
**valid test case numbers are: 01-10 (inclusive)**
