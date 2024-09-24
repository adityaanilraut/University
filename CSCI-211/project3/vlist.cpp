
// video.cpp
// Raut, Aditya Anil
// araut1


#include <iostream>
#include <string>

using namespace std;
#include "vlist.h"
#include "video.h"

// this function retuen a bool value if a video title already exits
// use for internal purposes
// returns True or False
bool Vlist::__ifexist(Video* newVideo){
    Node* current = m_head;

    while (current != nullptr) {
            if(current->m_video->getTittle()==newVideo->getTittle()){
                return false;

                }
            current = current->m_next;
            
        }
        return true;

}

// Purpose:inserts all the elememts in the list in sorted order by the length of their title
// sortedlinkedlist code was used to build this function
// Input Parameters: video node objects
// Output Parameters: void
// Return Value:  void



void Vlist::insert(Video* newVideo) {
    
        Node* newNode = new Node(newVideo, nullptr);

        
        if (m_head == nullptr) {// to insert the node at head if list is empty
            m_head = newNode;
        }
        else if (!Vlist::__ifexist(newVideo)) {// checker to find if the title of the new video exits or not
            cerr<<"Could not insert video <"<<newVideo->getTittle()<<">, already in list."<<endl;
        }
        
        else if (newVideo->getTittle() < m_head->m_video->getTittle()) {// to insert at head if the new node title is small then head
            newNode->m_next = m_head;
            m_head = newNode;
        }
        
        else {
            Node* current = m_head;      // to insert at tail if the new node title is bigger then tail for in between
            
            while (current->m_next != nullptr && current->m_next->m_video->getTittle() < newVideo->getTittle()) {
                current = current->m_next;
            }
            newNode->m_next = current->m_next;
            current->m_next = newNode;
        }
        
    }

// Purpose:print all the ojects in linkedlist
// Input Parameters: none
// Output Parameters:prints all objects
// Return Value:  void
void Vlist::print() {
        Node* current = m_head;
        while (current != nullptr) {
            current->m_video->print();
            current = current->m_next;
        }
    }

// Purpose:lookups if the video title in linkedlist and prints it
// Input Parameters: none
// Output Parameters:prints the lookup oject
// Return Value:  void
void Vlist::lookup(string title){
    //string title;
    //getline(cin, title);
    //cin.ignore();
    Node* current = m_head;
    int flag=0;
    while (current != nullptr) {
            if(current->m_video->getTittle()==title){
                current->m_video->print();
                flag=1;}
            current = current->m_next;
            
        }
    if(flag==0){
        cerr<<"Title <" <<title<<"> not in list."<<endl;
    }

    


}

// Purpose:removes the video objects for the programs
// Input Parameters: title of the video that you want to delete
// Output Parameters:none
// Return Value:  void
void Vlist::remove(string title){
    if (m_head==nullptr){// checking of list is empty
        cerr<<"Title <" <<title<<"> not in list, could not delete."<<endl;

        return;  // If list is empty
    }
    if (m_head->m_video->getTittle() == title) {// checking if obj is at head
        Node* temp = m_head;
        m_head = m_head->m_next;
        delete temp->m_video;
        delete temp;
        return;
        }
    else{             // checking of list is anywhere between the linkedlist till null and then removes it
    Node* current = m_head;
    Node* prev=m_head;
    int flag=0;
    while (current != nullptr) {
            if(current->m_video->getTittle()==title){
                Node* temp =current;
                prev->m_next=current->m_next;
                delete temp->m_video;
                delete temp;
                //current->m_video->print();
                flag=1;
                break;
                }
            prev=current;
            current = current->m_next;
            
        }
    if(flag==0){      //flags to indicate if the title is not found
        cerr<<"Title <" <<title<<"> not in list, could not delete."<<endl;
    }
    }


}
// Purpose:print the length of list
// Input Parameters: none
// Output Parameters:lenght
// Return Value:  int
int Vlist::length(){
    int count=0;
    Node* current = m_head;
    if (current==nullptr){
        return 0;
    }
    else{
    while (current != nullptr) {

        count=count+1;
        current=current->m_next;
    }
    }
    return count;


}