#include <iostream>

using namespace std;

#ifndef DSTACK_H
#define DSTACK_H


using namespace std;
class Dstack{
    private:
    class Node{
        public:
        double data;
        Node* next;
        Node(double d,Node* n){
            this->data=d;
            this->next=n;
            }
    };
    Node* head;
    //int size;
    public:
    Dstack(){
        head=nullptr;
        
    }
    ~Dstack(){
        Node* current=head;
        Node* previous=nullptr;
        
        while(current!=nullptr){
            previous=current;
            current=current->next;
            delete previous;
            //cout<<"distructor is called"<<endl;

        }
        
    }
    
    void push(double &value);
    double pop();
    int size();
    bool empty();
    void print();





};

#endif 