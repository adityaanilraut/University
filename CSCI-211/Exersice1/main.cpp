#include <iostream>

#include "course.h"
// Create a Car class with some attributes
using namespace std;


int main() {
  //course programming,english;

  course programming("CSCI", 211, 1000);
  course english("ENGL", 130, 1400);
  course physics("PHYS", 204, 800);



  programming.print();
  english.print();
  english.print();
  return 0;
}