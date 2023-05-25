#include "doubleLinkedList.h"
#include "Node.h"
#include "twoDimensionalLL.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


int main(){ 
    doubleLinkedList* dll = new doubleLinkedList();
    Node* n1 = new Node(new Stock("I0001", "apple","a",Price(1,1),10));
    Node* n2 = new Node(new Stock("I0002", "banana", "b", Price(1,1),12));
    Node* n3 = new Node(new Stock("I0003", "apricot", "A", Price(1,1),20));
    Node* n4 = new Node(new Stock("I0004", "date", "d", Price(1,1),20));
    Node* n5 = new Node(new Stock("I0005", "mango", "m", Price(1,1),20));
    Node* n6 = new Node(new Stock("I0006", "carrot", "c", Price(1,1),1));
    dll->append(n1);
    dll->append(n2);
    dll->append(n3);
    dll->append(n4);
    dll->append(n5);
    dll->append(n6);
    dll->~doubleLinkedList();
}
