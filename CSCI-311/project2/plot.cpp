#include <iostream>
#include <vector>
#include <matplotlibcpp.h>
using namespace std ;
namespace plt = matplotlibcpp ;
int main () {
vector < double > x = {1 , 2 , 3 , 4 , 5};
vector < double > y = {1 , 4 , 9 , 16 , 25};
plt :: plot (x , y ) ;
plt :: show () ;
}