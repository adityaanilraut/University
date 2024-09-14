

#include <iostream>
// Create a Car class with some attributes
using namespace std;

#include "course.h"

course::course(string d,int n,int t) {
    this->dept=d;
    this->number=n;
    this->time=t;
}

void course::print() {
    cout << this->dept << " "  << this -> number<< " "   << this->time <<endl;
}





