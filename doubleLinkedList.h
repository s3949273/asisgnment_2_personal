#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include "CashRegister.h"


class doubleLinkedList
{
public:
    doubleLinkedList();
    ~doubleLinkedList();

    void append(Node* node);
    void insert(Node* node, Node* prevNode);
    Node* goToIndex(int Index);
    /*
        params: Node* node: the node before the node you want to delete
    */
    bool remove(Node* node);
    
    //handles the payment in purchase item
    void insertionsort(bool SortBy);
    void write_to_stock_file(string stockfile);
    void write_to_coin_file();
    bool purchaseItem(CashRegister* till);
    void display_stock();
    void open_stock_file(string filepath);
    void reset_stock_count();
    string get_lowest_ID();
    void add_item();
    Node* searchID(string ID);
    void remove_item();
    Node* get_node(size_t index);
    unsigned get_count();

    void test();
private:
    // the beginning of the list
    Node* head;
    Node* tail;
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


