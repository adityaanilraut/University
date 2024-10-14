// sim.cpp
// Raut, Aditya Anil
// araut1
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream> 
#include "pqueue.h"
#include "cust.h"
using namespace std;
const int COST_PER_ITEM = 3;
const int SHOP_TIME_PER_ITEM = 2;
const int CHECKOUT_TIME_PER_ITEM = 1;
const int ROB_TIME = 7;
const int STARTING_CHECKER_CASH = 250;

struct Checker {
int m_cash=STARTING_CHECKER_CASH; // 
int m_done_time; 
bool status;
Cust *m_cust; 
};

bool is_valid_integer(char* a){
    if (a[0] == '\0') {
        return false;  
    }

    for (int i = 0; i < strlen(a); ++i) {
        if (!isdigit(a[i])) {
            return false;
        }
}
return true;
}


// Purpose:Program start here
// Input Parameters: takes input from the command line
// Output Parameters: write the output to the output file
// Return Value: Always returns 0 if pass
int main(int argc, char* argv[]) {
    
    if (argc != 5) {
        cerr << "Error: invalid number of command line arguments."<< endl;
        return 1; 
    }
    
    int checker_count = atoi(argv[1]);    
     if (checker_count < 1|| !is_valid_integer(argv[1])) {
        cerr << "Error: invalid number of checkers specified." << endl;
        
        return 1;
    }
    int checker_break_duration = stoi(argv[2]);    
    if (checker_break_duration < 0 || !is_valid_integer(argv[2])) {
        cerr << "Error: invalid checker break duration specified." << endl;
        return 1;
    }
    string inputFile = argv[3];  
    string outputFile = argv[4];

    ifstream my_ifile(inputFile);
    if (!my_ifile) {
        cerr << "Error: could not open input file <" << inputFile << ">." << endl;
        return 1; // Error condition
    }
    

    // Open the output file
    ofstream my_ofile(outputFile);
    if (!my_ofile) {
        cerr << "Error: could not open input file <" << outputFile << ">." << endl;
        return 1; 
    }

    string buffer;
    string name;
    string cusRob;
    
    int a;
    int b;
    PQueue pq;



    // Example: Processing the input file and writing to the output file
    while (getline(my_ifile, buffer)) {
        // Process each line if needed; for now, just copy the line to the output file
        //my_ofile << buffer << endl;
        istringstream iss(buffer);
        iss >>name >> cusRob >> a >> b;
        //if (cusRob=="robber") {a=-10000;}
        pq.enqueue(new Cust(name, cusRob=="robber", a, b),a);
    }
    int customer_count = pq.size();
    //Cust *aaa=pq.dequeue();
    //Cust *aaaa=pq.dequeue();
    //Cust *aaaaa=pq.dequeue();
    

    PQueue shopingq;
    PQueue checkout;
    Checker* checkers = new Checker[checker_count];
    for (int i = 0; i < checker_count; i++) {
        checkers[i].m_done_time = 0;
        checkers[i].m_cash = STARTING_CHECKER_CASH;
        checkers[i].status=true;
        checkers[i].m_cust = nullptr;
    }
    //pq.print();
    int clock=1;
    
// Purpose:This runs simulation of the shop
// Input Parameters: takes pqueue as input
// Output Parameters: write the output to the output file

 while (customer_count > 0) {
    

    // Customer enters store
    while (!pq.isEmpty() && pq.getFirstPriority() == clock) {
        Cust *tempcust = pq.dequeue();
        tempcust->printEnteredStore(my_ofile, clock);
        shopingq.enqueue(tempcust, clock + tempcust->getItemCount() * SHOP_TIME_PER_ITEM);
    }

    // Customer finishes shopping
    while (!shopingq.isEmpty() && shopingq.getFirstPriority() == clock) {
        Cust *tempcust = shopingq.dequeue();
        //my_ofile << clock << ": " << tempcust->getName() << " done shopping" << endl;
        tempcust->printDoneShopping(my_ofile, clock);
        
        bool assignedChecker = false;
        if (!assignedChecker) {
            checkout.enqueue(tempcust, 0);
        }
        

    }
    
    

    for (int i = 0; i < checker_count; i++) {
            
            
            if (checkers[i].m_cust != nullptr && checkers[i].m_done_time == clock) {
                // Finish checkout
                Cust* cust = checkers[i].m_cust;
                if (cust->getIsRobber()) {
                   
                    //37: Maggie stole $277 and 1 item from checker 0
                    //string tempp;
                    //if(cust->getItemCount()>1){ tempp="s";} else{ tempp="";}
                    //my_ofile<<clock<<": "<<cust->getName()<<" stole $"<<checkers[i].m_cash<<" and " <<cust->getItemCount()<<" item"<<tempp<<" from checker "<<i<<endl;
                    //my_ofile<<cust->getName()<<" "<<clock<<" "<<i<<"checker cash"<<checkers[i].m_cash<<"cust->getItemCount()"<<cust->getItemCount()<<endl;
                     cust->printStole(my_ofile, clock, checkers[i].m_cash, cust->getItemCount(), i);
                    checkers[i].m_cash = 0;
                    checkers[i].m_done_time = clock + checker_break_duration;
                } else {
                    int payment = cust->getItemCount() * COST_PER_ITEM;
                    //20: Edna paid $9 for 3 items to checker 2
                    //string tempp;
                    //if(cust->getItemCount()>1){ tempp="s";} else{ tempp="";}
                    //my_ofile<<clock<<": "<<cust->getName()<<" paid $"<<payment<<" for "<<cust->getItemCount()<<" item"<<tempp<<" to checker "<<i<<endl;

                    cust->printPaid(my_ofile, clock, payment, cust->getItemCount(), i);
                    checkers[i].m_cash += payment;
                }
                delete cust;
                checkers[i].m_cust = nullptr;
                customer_count--;
                //clock=clock-1;
            }
        }
            for (int i = 0; i < checker_count; i++){
                if (checkers[i].m_cust == nullptr && checkers[i].m_done_time <= clock && !checkout.isEmpty()) {
                    // Start new checkout
                    Cust* cust = checkout.dequeue();
                    checkers[i].m_cust = cust;
                    //20: Apu started checkout with checker 0
                    //my_ofile<<clock<<": "<<cust->getName()<<" started checkout with checker "<<i<<endl;
                    cust->printStartedCheckout(my_ofile, clock, i);

                    //my_ofile<<cust->getName()<<" "<<clock<<" "<<i;
                    int checkout_time;
                    if (cust->getIsRobber()){
                        checkout_time = ROB_TIME;
                    }
                    else{
                        checkout_time = cust->getItemCount() * CHECKOUT_TIME_PER_ITEM;
                    }

                    checkers[i].m_done_time = clock + checkout_time;
                }
            }
            
        

       clock++;
    //if (clock == 2000) {
    //    break;
   // }
    }

    for (int i = 0; i < checker_count; i++){
    my_ofile<<"registers["<<i<<"] = $"<<checkers[i].m_cash<<endl;
    }
    my_ofile<<"time = "<<clock<<endl;


    //shopingq.print();
    //checkout.print();
    

    return 0;
}