#include "doubleLinkedList.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <dirent.h>
#include "helper.h"
#include <fstream>
#define EOF_ERROR_MESSAGE "ctrl^d detected"
#define COLOR_RED   "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"

#define RESET_TEXT_TO_NORMAL   "\x1b[0m"


using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::ofstream;

doubleLinkedList::doubleLinkedList() {
   this->head = nullptr;
   this->tail = nullptr;
   this->count = 0;
}

doubleLinkedList::~doubleLinkedList() {
    Node* head = this->head;
    if (this->head != nullptr){
        for(unsigned x = 0; x<this->count; x++){
            Node* cur = head;
            cout<<cur->data->name<<endl;
            head = head->next;
            delete cur;
            cur = nullptr;
        }
    }
};

void doubleLinkedList::insert(Node* node, Node* prevNode){
    if (prevNode == nullptr){
        this->head->prev = node;
        node->next = this->head;
        node->prev = nullptr;
        this->head = node;
    }else{
        if (this->head->next == nullptr){
            node->prev = this->head;
            this->tail = node;  
            node->next = nullptr;
        }
        node->prev = prevNode;
        node->next  = prevNode->next;
        prevNode->next->prev = node;
        prevNode->next = node;    

    }
}

void doubleLinkedList::insertionsort(bool SortBy){
    Node* currentNode = this->head;
    for (size_t i = 1;i<this->count;i++){
        currentNode = currentNode->next;
        Node* head = this->head;
        if (SortBy){
            // sort by Name
            size_t j = 0;
            while (currentNode->data->name > head->data->name && j< i){
                head = head->next;
                j++;
            }
            if (j != i){
                this->get_node(i-1)->next = currentNode->next;
                if(i+1 < this->count){
                    this->get_node(i+1)->prev = currentNode->prev;
                }else{
                    this->tail = this->get_node(i-1);
                }
                this->insert(currentNode, head->prev);
                currentNode = this->get_node(i);
            }
        }else{// sort by ID
            size_t j = 0;
            while (currentNode->data->id > head->data->id && j<i){
                head = head->next;
                j++;
            }
            if (j != i){
                this->get_node(i-1)->next = currentNode->next;
                if(i+1 < this->count){
                    this->get_node(i+1)->prev = currentNode->prev;
                }else{
                    this->tail = this->get_node(i-1);
                }
                this->insert(currentNode, head->prev);
                currentNode = this->get_node(i);
            }
        }
        
    }
}   

void doubleLinkedList::open_stock_file(string filepath){
    try{
        ifstream stocks(filepath);
        string line_stock;
        vector<string> output_stock;
        while (getline(stocks, line_stock)){
            Helper::splitString(line_stock, output_stock, "|");
            if (output_stock.size() > 5){
                throw std::invalid_argument(
                    "Too many attributes given "
                    "to build a stock object"
                );
            }
            vector<string> given_price;
            Helper::splitString(output_stock[3],given_price, ".");
            if (given_price.size() != 2 || given_price.at(1).empty() || given_price.at(1).size() >2){
                throw std::invalid_argument(
                    "Price had invalid values when making the price object"
                );
            }
            try{
                Node* new_node = new Node(
                    new Stock(
                        output_stock[0],
                        output_stock[1],
                        output_stock[2],
                        Price(stoi(given_price[0]), stoi(given_price[1])),
                        (stoi(output_stock[4]))
                    )
                );
                this->append(new_node);
            }catch(std::exception& e){
                cout<<e.what()<<endl;
            }
            output_stock.clear();
        }
        stocks.close();
    }catch(std::exception& e){
        cout<<e.what()<<endl;
    }
};

Node* doubleLinkedList::searchID(std::string ID){
    Node* ret = nullptr;
    Node* head = this->head;
    //found used to prematurely break out of the while loop when the ID is found
    bool found = false;
    if (head != nullptr){
        while (head->next != nullptr && found == false){
            if (ID == head->data->id){
                found = true;
                ret = head;
            }
            head = head->next;
        }
        //in the case that the head is the tail
        if(ID == head->data->id){
                found = true;   
                ret = head;
        }
    };
    if (this->head == nullptr && !found){
        //there was no stock in the linkedlist
        cout<<"No stock in the linked list\n"<<endl;
        // throw std::out_of_range("No stock in the linkedlist");
    }if (!found){
        //there was stock in the linkedlist but the id wasn't found
        cout<<"Couldn't find the ID in the stock\n"<<endl;
        // throw std::out_of_range("couldn't find the ID in the stock");
    }
    return ret;
};
//REQ 7
void doubleLinkedList::add_item(){
    bool loop = true;
    while (loop) {
        try{
            if (cin.eof()){
                loop=false;
                throw std::runtime_error("");
            }
            string id = this->get_lowest_ID(); 
            cout<<"The id of the new stock will be: "<<id<<"\n"<<endl;
            //Name input
            cout<<"Enter item name: ";
            string name_input = Helper::readInput();
            //Check length of name
            if (cin.eof()){throw std::runtime_error("");loop=false;}
            if (name_input.size() > NAMELEN) {
                throw std::invalid_argument(
                    "Maximum length reached "
                    "for product name"
                );
            }
            
            //Item description input
            cout<<"Enter item description: ";
            string desc_input = Helper::readInput();
            
            //Check length of description
            if (cin.eof()){loop=false;throw std::runtime_error("");}
            if (desc_input.size() > DESCLEN) {
                throw std::invalid_argument(
                    "Maximum length reached "
                    "for product description"
                );
            }
            
            //Item price input
            cout<<"Enter the price for the item: ";
            string price_input = Helper::readInput();
            if (cin.eof()){loop=false;throw std::runtime_error("");}
            vector<string> price_split;
            Helper::splitString(price_input, price_split, ".");
            if (stoi(price_input) < 0 || price_split.size() != 2 || price_split.at(1).size() != 2){
                throw std::invalid_argument(
                    "Price was not correctly formatted"
                );
            }
            Node* new_node = new Node(
                new Stock(
                    id, 
                    name_input, 
                    desc_input, 
                    Price(stoi(price_split[0]), stoi(price_split[1])), 
                    DEFAULT_STOCK_LEVEL
                )
            );
            this->append(new_node);
            cout<<"\""<<name_input<<", "<<desc_input<<".\" has now been added to the menu.\n"<<endl;
            loop = false;
        }
        catch(std::runtime_error& e){}
        catch(std::exception& e){
            cout << e.what() << "\n" << endl;
        }
    }
}
//REQ 5
bool doubleLinkedList::purchaseItem(CashRegister* cr){
    bool ret = false;
    try{
        cout<<"Please enter the id of the item you wish to purchase: ";
        string input = Helper::readInput();
        if(cin.eof()){throw std::runtime_error("");}
        Node* item_to_purchase = this->searchID(input);
        while (item_to_purchase==nullptr){
            if(cin.eof()){
                throw std::runtime_error("");
            }
            cout<<"Please enter the id of the item you wish to purchase: ";
            input = Helper::readInput();
            item_to_purchase = this->searchID(input);
        }
        vector<int>valid_denoms = {5,10,20,50,100,200,500,1000};
        
        if (item_to_purchase->data->on_hand <=0){
            throw std::invalid_argument("Not enough stock for the item you tried to purchase");
        }
        cout<<"You have selected ";
        cout<<item_to_purchase->data->name<<" - ";
        cout<<item_to_purchase->data->description<<". ";
        cout<<"This will cost you: ";
        int price_of_item = item_to_purchase->data->price.dollars*100+item_to_purchase->data->price.cents;
        if(price_of_item/100.0 >=1){
            printf("$%.2f \n", price_of_item/100.0);
        }else{
            cout<<price_of_item<<"c"<<endl;
        }
        cout<<"Please hand over the money - type in the value of each note/coin in cents."<<endl;
        cout<<"Please press enter or ctrl-d on a new line to cancel this purchase: ";
        vector<unsigned> given_coins(8,0);
        int to_give = price_of_item;
        bool valid_input = true;
        while (to_give >0 && valid_input){
            string input = Helper::readInput();
            if(cin.eof()){
                throw std::invalid_argument("");
            }
            if(input.empty()){
                    valid_input = false;
            }
            if(valid_input){
                //just so that it doesn't unecessarily print all this stuff
                if(Helper::isNumber(input)){
                    int given_cents = stoi(input);
                    if(Helper::is_valid_denom(given_cents)){
                        given_coins.at(cr->get_index_for_denom(given_cents))++;
                        to_give -= given_cents;
                    }else{
                        cout<<"Error: ";
                        if(given_cents >= 100){
                            printf("$%.2f ",given_cents/100.0);
                        }else{
                            cout<<given_cents<<"c ";
                        }
                        cout<<"is not a valid denomination of money. Please try again"<<endl;
                    }
                }else{
                    cout<<"invalid input for coin, not a number"<<endl;
                }
                if(to_give/100.0 >=1){
                    cout<<"You still need to give us ";
                    // cout<<"$"<<to_give/100.0<<endl;
                    printf("$%.2f: ", to_give/100.0);
                }else if(to_give >0){
                    cout<<"You still need to give us ";
                    cout<<to_give<<"c : ";
                }
            }
        }          
        if(to_give == 0){
            //if you give it exactly the amount of money it requires
            for(size_t x=0; x<cr->coins.size(); x++){
                cr->coins.at(x)->count+=given_coins.at(x);
            }
            cout<<"Here is your change: "<<item_to_purchase->data->name<<endl;
            item_to_purchase->data->on_hand--;
            ret = true;
        }else if (to_give > 0){
            //interupted in the middle of the while loop
            if (to_give < price_of_item){
                //the user acutally gave some coins so we have to return them
                cout<<"Here is your change: "<<endl;            
                for(size_t x=0; x<given_coins.size(); x++){
                    if (given_coins.at(x)>0){
                        for (unsigned y = 0; y<given_coins.at(x); y++){
                            if(valid_denoms.at(x) >= 100){
                                //dollar or more
                                cout<<"$"<<(valid_denoms.at(x)/100)<<" ";
                            }else{
                                //in the cents
                                cout<<valid_denoms.at(x)<<"c ";
                            }
                            given_coins.at(x)--;
                        }
                    }
                }
                cout<<endl;
            }
        }else if(to_give < 0){
            //you are entitled to change
            for(size_t x = 0; x<given_coins.size(); x++){
                cr->coins.at(x)->count += given_coins.at(x);
            }
            bool x = cr->do_change(abs(to_give));
            if (x){
                cout<<"Here is your: "<<item_to_purchase->data->name<<"\n"<<endl;
                item_to_purchase->data->on_hand--;
                ret = true;
            }else{
                //not enough money in the register
                cout<<"Sorry, there wasn't enough coins in the register to give you your change. :"<<endl;
                cout<<"Here are your coins back"<<endl;
                for(size_t x=0; x<given_coins.size(); x++){
                    if (given_coins.at(x)>0){
                        for (unsigned y = 0; y<given_coins.at(x); y++){
                            if(valid_denoms.at(x) >= 100){
                                //dollar or more
                                cout<<"$"<<(valid_denoms.at(x)/100.0)<<" ";
                            }else{
                                //in the cents
                                cout<<valid_denoms.at(x)<<"c ";
                            }
                            given_coins.at(x)--;
                            cr->coins.at(x)->count--;
                        }
                    }
                }
                cout<<endl;
            }
        }
    }
    catch(std::exception& e){
        // cout<<e.what()<<endl;
        // ret = this->purchaseItem(cr);
    }
    return ret;
}

Node* doubleLinkedList::get_node(size_t index){
    Node* ret = nullptr;
    if (index <= this->count){
        //only do something if the index the person wants to 
        //get to is less than the size of the linkedlist
        ret = this->head;
        while (ret->next!= nullptr && index > 0){
            ret = ret->next;
            index --;
        }
    }
    return ret;
}

void doubleLinkedList::append(Node* currentNode){
    //complete?
    
    if(this->head == nullptr){
        this->head = currentNode;
        this->head->prev = nullptr;
        this->head->next = nullptr;
        this->tail = currentNode;   
    }else{
        if(this->head->data->name > currentNode->data->name){
            currentNode->next = this->head;
            currentNode->prev = nullptr;
            this->head->prev = currentNode;
            this->head = currentNode;
        }
        else{
            if(this->tail == this->head){
                if(this->head->data->name < currentNode->data->name){
                    //append to the end of the list
                    currentNode->next = nullptr;
                    currentNode->prev = this->head;
                    this->head->next = currentNode;
                    this->tail = currentNode;
                }else{
                    //append to the head and push the head down
                }
            }
            else{
                Node* cur = this->head;
                while (cur->next != nullptr && cur->data->name < currentNode->data->name){
                    cur = cur->next;
                }
                if(cur == this->tail && cur->data->name < currentNode->data->name){
                    currentNode->next = nullptr;
                    currentNode->prev = this->tail;
                    this->tail->next = currentNode;
                    this->tail = currentNode;
                }else{
                    currentNode->next = cur;
                    currentNode->prev = cur->prev;
                    cur->prev->next = currentNode;
                    cur->prev = currentNode;
                }
            }
        }
    }
    this->count ++;
}

void doubleLinkedList::test(){
    Node* node = this->tail;
    cout << "backwards: ";
    while (node!=nullptr){
        cout << node->data->name << ", ";
        node = node->prev;
    }
    cout <<endl;
}
//REQ 8
void doubleLinkedList::remove_item(){
    cout<<"Please enter the ID of the item you'd like to remove: ";
    string id = Helper::readInput();
    while (id.empty()){
        cout<<"Please enter the ID of the item you'd like to remove: ";
        id = Helper::readInput();
        if(cin.eof()){
            id = "EOF";
            printf(COLOR_RED BOLD_TEXT EOF_ERROR_MESSAGE COLOR_RESET "\n");
        }
    }
    if (id.find("I") != string::npos && id.size() == 5 && !cin.eof()){
        Node* curnode = this->head;
        size_t i = 0;
        while (i<this->count && curnode->data->id != id){
            curnode = curnode->next;
            i++;
        }
        if (curnode->prev == nullptr){
            //delete head
            this->head =  this->head->next;
            cout << "This item \"" <<curnode->data->id <<" - " <<curnode->data->name << " - " << curnode->data->description << ".\" has now been removed from the system.\n"<<endl;
            this->head->prev = nullptr;
            delete curnode;
            this->count--;
        }else if(i < this->count){
            if(i== this->count-1){
                //deleting the tail
                this->tail = this->tail->prev;
                this->tail->next = nullptr;
                // this->tail = curnode->prev;
                delete curnode;
            }else{
                //deleting inner nodes
                curnode->prev->next = curnode->next;
                curnode->next->prev = curnode->prev;
                cout << "This item \"" <<curnode->data->id <<" - " <<curnode->data->name << " - " << curnode->data->description << ".\" has now been removed from the system.\n"<<endl;
                delete curnode;
                this->count--;    
            }
        }else{
            cout<<"The id was not found"<<endl;
        }
        
    }else{
        if(!cin.eof()){
            cout<<"you tried to remove with an invalid id"<<endl;
            }
    }
}

void doubleLinkedList::reset_stock_count(){
    Node* head = this->head;
    for(size_t x = 0; x<this->count; x++){
        head->data->on_hand  = DEFAULT_STOCK_LEVEL;
        head = head->next;
    }
}

string  doubleLinkedList::get_lowest_ID(){
    string ret = "";
    if (this->head != nullptr){
        insertionsort(false);
        unsigned int i = 0;
        int a = 0;
        Node* currentNode = this->head;
        while (i < this->count-1 && ret == ""){
            currentNode->prev->data->id = currentNode->data->id;
            currentNode = currentNode->next;
            a = Helper::strip_ID(currentNode->prev->data->id);
            int b = Helper::strip_ID(currentNode->data->id);
            if (a!=-1 && b!= -1 && a+1<b){
                a+=1;
                ret = currentNode->prev->data->id;
            }
            i++;
        }
        if (ret == ""){
            a = this->count+1;
        }
            ret =  Helper::generate_ID(a);
        insertionsort(true);
    }
    else { 
        ret = "I0001";
    }
    return ret;
}

void doubleLinkedList::write_to_stock_file(string stockfile){
    // insertionsort(false);
    Node* curNode = this->head;
    string s = "";
    while(curNode != nullptr){
        s += curNode->data->id + "|"+curNode->data->name + "|" + curNode->data->description + "|"+
        std::to_string(curNode->data->price.dollars) + "." + std::string(2 - std::to_string(curNode->data->price.cents).length(),'0') + std::to_string(curNode->data->price.cents)
        + "|" + std::to_string(curNode->data->on_hand) + "\n";
        curNode = curNode->next;
    }
    ofstream MyFile(stockfile);
    MyFile << s;
    MyFile.close();
    insertionsort(true);
}

void doubleLinkedList::display_stock(){
    cout<<"Items Menu"<<endl;
    cout<<"----------"<<endl;
    cout.width(46);
    cout<<std::left<<"ID   | Name";
    cout<<"| Available | Price"<<endl;
    for (unsigned x=0; x < 65; x++){
        cout<<"-";
    }
    cout<<endl;
    if (this->head == nullptr){
        cout<<"no items to show"<<endl;
    }else{
        Node* head = this->head;
        for(size_t x = 0; x<this->count; x++){
            Stock* cur = head->data;
            if(cur->on_hand >= 20){
                printf(COLOR_GREEN);
            }
            else if(cur->on_hand >= 10){
                printf(COLOR_YELLOW);
            }
            else if(cur->on_hand < 10){
                printf(COLOR_RED);   
            }
            
            cout<<cur->id<<"|";
            cout.width(40);
            cout<<std::left<<cur->name<<"|";
            cout.width(11);
            cout<<std::left<<cur->on_hand;
            cout<<"| ";
            cur->price.display();
            printf(RESET_TEXT_TO_NORMAL);
            head = head->next;
        }
        //print the tail
        // cout<<"tail: "<<this->tail->data->name<<endl;
    }
    cout<<endl;
}
