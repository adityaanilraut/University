#include<iostream>
using namespace std;
#include"linkedlist.h"



void Linkedlist::push(double &value){
    head=new Node(value,head);
}
bool Linkedlist::pop(){
    Node* current=head;
    cout<<"pop value"<<head->data<<endl;
    head=head->next;
    delete current;



}
int Linkedlist::size(){
    Node* current=head;
    int size=0;
    while(current!=nullptr){
        
        size=size+1;
        current=current->next;
        
    }
    cout<<"size is "<<size<<endl;



}
bool Linkedlist::empty(){



}
void Linkedlist::print(){
    Node* current=head;
    while(current!=nullptr){
        
        cout<<current->data<<endl;
        current=current->next;
        
    }
}