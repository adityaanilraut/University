#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "dstack.h"

bool operations(Dstack &l1,char sign){
    double nums2;
    double nums1;
    if(l1.size()>1){
        nums2=l1.pop();
        nums1=l1.pop();
    }
    else{
        throw "Error: Invalid expression.";
    }
    switch(sign) {
        case '+':
            nums2=nums1+nums2;
            break;
        case '-':
            nums2=nums1-nums2;
            break;
        case '*':
            nums2=nums1*nums2;
            break;
        case '/':
            if (nums2==0)
            {
               throw "Error: Invalid expression.";
            }
            
            nums2=nums1/nums2;
            break;
        case '^':
            if (nums1<0&&nums2!=int(nums2))
            {
               throw "Error: Invalid expression.";
            }
            else if(nums1==0 && nums2<0){
                throw "Error: Invalid expression.";

            }
            nums2=pow(nums1,nums2);
            break;
        }
    l1.push(nums2);
    return true;
}

int main(){
    Dstack l1= Dstack();
    char a1;
    string s;
    double ss;
    try
    {
    while ( !cin.eof()) {
        
        cin.get(a1);
        if(isdigit(a1)){
            s=s+a1;
            }
        else if(a1=='.'){
            
            if(s.find('.')!=-1){
                throw "Error: Invalid expression.";
            }
            
            
            s=s+a1;
        }
        
        
        
        else if(isspace(a1)&&!s.empty()){
            if (s == ".")
            {
                throw "Error: Invalid expression.";
            }
            
            ss=stod(s);
            l1.push(ss);
            s.clear();
        }
        else if(a1=='+'||a1=='-'||a1=='*'||a1=='/'||a1=='^'){
            if(!s.empty()){
                ss=stod(s);
                l1.push(ss);
                s.clear();}
            if(!operations(l1,a1)){
                throw "Error: Invalid expression.";
                }
    }
 
    }
    if (l1.size()!=1){
       throw "Error: Invalid expression.";
        }
        double result = l1.pop();
        cout<<result<<endl;

        }
    catch(const char* e)
    {
       cerr <<"Error: Invalid expression."<< endl;
       return 1;
    }
        return 0;
}