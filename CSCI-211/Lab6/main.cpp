#include<iostream>
using namespace std;
#include"linkedlist.h"
int main(){
    Linkedlist l1= Linkedlist();
    string a;

    while (getline(cin, a)) {

        double aa=stod(a);
        cout<<aa<<endl;
        l1.push(aa);
        //cin.ignore();
    }
    l1.pop();
    l1.pop();
    l1.size();
    l1.print();

}