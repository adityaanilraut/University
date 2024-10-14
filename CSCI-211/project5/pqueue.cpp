// pqueue.cpp
// Raut, Aditya Anil
// araut1

#include <iostream>
#include "pqueue.h" 
#include "cust.h" 
using namespace std;




PQueue::Node::Node(Cust *data, int priority, Node* next){

    this->data=data;
    this->priority=priority;
    this->next=next;
}
    

PQueue::PQueue() {
    head=nullptr;
}



// enqueue function inserts an element with given data and priority into the priority queue
// The element is inserted according to its priority in descending order  (highest priority first)
// If two elements have the same  priority, they maintain their relative order (stable priority queue)
void PQueue::enqueue(Cust *data, int priority) {
    Node* newNode = new Node(data, priority,head);


    // If the list is empty or the priority is higher  than the head node's priority,
    // insert the new  node at the beginning of the list
    if (!head || priority < head->priority) {
        newNode->next = head;
        head = newNode;

    } else {
        // Traverse the  list to find the correct position for the new node
        Node* current = head;
        while (current->next && priority >= current->next->priority) {
            current = current->next;
        }
        // Insert the new node after the current node
        newNode->next = current->next;
        current->next = newNode;
    }
}

// dequeue() function removes  and returns the data of the element with the highest priority
// If the priority queue is empty, an exception  is thrown
Cust* PQueue::dequeue() {

    
if (head==nullptr) {
    throw runtime_error("Empty priority queue");
}

// Remove the head node from the list and save its data
Node* temp = head;
Cust* data = temp->data;
head = head->next;

// Deallocate memory used by the  removed node and return its data
delete temp;
return data;
}

// isEmpty() function checks if the priority queue is empty
// Returns true if the head node is nullptr (no elements in the list) , false  otherwise
bool PQueue::isEmpty() {
return head == nullptr;
}
//just for testing -- not using now //  
void PQueue::print(){
Node* current=head;
while(current!=nullptr){
    cout<<current->data->getName()<<' '<<current->data->getIsRobber()<<' '<<current->data->getArrivalTime()<<' '<<current->data->getItemCount()<<endl;
    current=current->next;
    }
}
int PQueue::getFirstPriority(){
    if(head==nullptr)
    {
        return 0;
    }
    return head->priority;
}


int PQueue::getshoptime(){
    if(head==nullptr)
    {
        return 0;
    }
    return head->data->getArrivalTime()+head->data->getItemCount()*2;


}
int PQueue::size() {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}



