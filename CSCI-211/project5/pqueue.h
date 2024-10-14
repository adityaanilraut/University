// pqueue.h
// Raut, Aditya Anil
// araut1
#include <iostream>
#include <stdexcept>
#include "cust.h" // Include the Cust class header file
using namespace std;
#ifndef PQUEUE_H
#define PQUEUE_H
class PQueue
{
private:
    class Node
    {
    public:
        Cust *data;
        int priority;
        Node *next;

        Node(Cust *data, int priority, Node* next);
    };

    

public:
    Node *head;
    PQueue();
    //~PQueue();
    void enqueue(Cust *cust, int priority);
    Cust *dequeue();
    void print();
    
    bool isEmpty();
    int getFirstPriority();
    int getPriority(Node* current);
    int getshoptime();
    int getsize();
    int size();
};
#endif
