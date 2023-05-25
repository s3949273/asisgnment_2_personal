.default: all

all: test

clean:
	rm -rf test *.o *.dSYM

test: Coin.o Node.o doubleLinkedList.o helper.o CashRegister.o test.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^ 

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
