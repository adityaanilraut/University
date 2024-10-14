// cust.h
// Raut, Aditya Anil
// araut1

#include<iostream>
#include<string.h>
using namespace std;

#ifndef CUST_H
#define CUST_H
class Cust
{
private:
    string name;
    bool isRobber;
    int arrivalTime;
    int items;
public:
Cust(string name, bool is_robber, int arrival_time, int item_count);
string getName();
bool getIsRobber();
int getArrivalTime();
int getItemCount();
void print(ostream &os);
void printEnteredStore(ostream &os, int clock) ;
void printDoneShopping(ostream &os, int clock) ;
void printStartedCheckout(ostream &os, int clock, int checker) ;
void printPaid(ostream &os, int clock, int amount, int items, int checker) ;
void printStole(ostream &os, int clock, int amount, int items, int checker) ;
    
};
#endif //CUST_H

