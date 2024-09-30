#include<iostream>
#include"dstack.h"
using namespace std;




void Dstack::push(double &value){
    head=new Node(value,head);
}
double Dstack::pop(){
    Node* current=head;
    //cout<<"pop value"<<head->data<<endl;
    head=head->next;
    
    double a=current->data;
    delete current;
    return a;
    



}
int Dstack::size(){
    Node* current=head;
    int size=0;
    while(current!=nullptr){
        
        size=size+1;
        current=current->next;
        
    }
    //cout<<"size is "<<size<<endl;
    return size;



}
bool Dstack::empty(){
    return true;



}
void Dstack::print(){
    Node* current=head;
    while(current!=nullptr){
        //cout<<"hellooooooo";
        cout<<current->data<<endl;
        current=current->next;
        
    }
}

