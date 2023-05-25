//incomplete
#ifndef TWODIMENSIONALL_H
#define TWODIMENSIONALL_H
#include "LinkedList.h"
#include "Node.h"
class twoDimensionalLL{
    public:
        twoDimensionalLL(){
            this->data = nullptr;
            this->next = nullptr;
            this->prev = nullptr;
        }
        twoDimensionalLL(LinkedList* ll){
            this->data = ll;
            this->next = nullptr;
            this->prev = nullptr;
        }
        void addnewNode();
        void removeLL(size_t x);
        void appendLL(size_t x);
    private:
        LinkedList* data;
        LinkedList* next;
        LinkedList* prev;
};


#endif