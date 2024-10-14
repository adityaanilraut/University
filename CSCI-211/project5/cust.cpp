// cust.cpp
// Raut, Aditya Anil
// araut1

#include "cust.h"
#include <cassert>
#include <cassert>

Cust::Cust(string name, bool isRobber, int arrivalTime, int items){
    this->name=name;
    this->isRobber=isRobber;
    this->arrivalTime=arrivalTime;
    this->items=items;
}
string Cust::getName(){
    return this->name;
}
bool Cust::getIsRobber(){
    return this->isRobber;
}
int Cust::getArrivalTime(){
    return this->arrivalTime;
}
int Cust::getItemCount(){
    return this->items;
}

void Cust::printEnteredStore(ostream &my_ofile, int clock)
{
    assert(clock == arrivalTime);
    my_ofile << clock << ": " << name << " entered store" << endl;
}

void Cust::printDoneShopping(ostream &my_ofile, int clock)
{
    my_ofile << clock << ": " << name << " done shopping" << endl;
}

void Cust::printStartedCheckout(ostream &my_ofile, int clock, int checker)
{
    my_ofile << clock << ": " << name << " started checkout with checker " << checker << endl;
}

void Cust::printPaid(ostream &my_ofile, int clock, int amount, int items, int checker)
{
    string temm;
    if (items > 1)
    {
        temm = "s";
    }
    else
    {
        temm = "";
    }
    my_ofile << clock << ": " << name << " paid $" << amount << " for " << items
       << " item" << temm << " to checker " << checker << endl;
}

void Cust::printStole(ostream &my_ofile, int clock, int amount, int items, int checker)
{
    string temm;
    if (items > 1)
    {
        temm = "s";
    }
    else
    {
        temm = "";
    }
    my_ofile << clock << ": " << name << " stole $" << amount << " and " << items
       << " item" << temm << " from checker " << checker << endl;
}

