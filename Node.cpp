#include "Node.h"
#include <iostream>


using std::cout;
using std::endl;

Price::Price(unsigned dollars, unsigned cents){
    this->dollars = dollars;
    this->cents = cents;
}


void Price::display(){
    cout<<"$"<<this->dollars<<".";
    if (this->cents < 10){
        cout<<"0";
    }
    cout<<cents<<endl;
}

Stock::Stock(string id, string name, string description, Price price, unsigned int on_hand):
    id(id), 
    name(name), 
    description(description),
    price(price), 
    on_hand(on_hand){
};
Stock::~Stock(){
}
Price::~Price(){
}

// };
Node::Node(){
    this->data = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
}

Node::Node(Stock* stock):data(stock), next(nullptr), prev(nullptr){
};
Node::Node(Node& other):data(other.data), next(other.next), prev(other.prev){}

Node::~Node(){
    delete this->data;
    this->next = nullptr;
    this->prev = nullptr;
};

bool Node::Update(Stock value){
    bool ret = false;
    try{
        this->data = &value;
        ret = true;
    }catch(std::exception& e){
        printf(COLOR_RED);
        cout<<"failed to update the node value"<<endl;
        printf(RESET_BOLD);
    }
    return ret;
}
