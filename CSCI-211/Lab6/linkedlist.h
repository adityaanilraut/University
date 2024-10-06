#include<iostream>
using namespace std;
class Linkedlist{
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
    Linkedlist(){
        head=nullptr;
        
    }
    ~Linkedlist(){
        Node* current=head;
        Node* previous=nullptr;
        
        while(current!=nullptr){
            previous=current;
            current=current->next;
            delete previous;
            cout<<"distructor is called"<<endl;

        }
        
    }
    
    void push(double &value);
    bool pop();
    int size();
    bool empty();
    void print();





};