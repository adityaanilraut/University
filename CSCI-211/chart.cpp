// chart.cpp
// Raut, Aditya Anil
// araut1
#include <iostream>
using namespace std;

// Purpose:Find the largest number in an array a
// Input Parameters: integer array , size of array
// Output Parameters: largest number in an array
// Return Value: The largest number in an array
int find_largest(int *arr,int size){
    int num=0;
    for(int i=0;i<size;i++){
        if(arr[i]>num){
            num=arr[i];
        }
    }
    //cout<<num;
    return num;
}

// Purpose: Print the bar chart based on the input array
// Input Parameters: integer array, size of the array, largest number in the array
// Output Parameters: None
// Return Value: None

void print_function(int *arr,int size){
    int largest_num=find_largest(arr,size);//the print_function calls find_largest function to get largest number of array.
    int flooor=largest_num;                // floor is equal to largest number.
    for(int i=0;i<largest_num;i++){
        for(int j=0;j<size;j++){
            if(arr[j]>flooor-1){
                cout<<"*";                 // will print "*" if when array element is greater than floor. 
            }
            else{
                cout<<" ";                 // will print " " if when array element is lesser than floor. 
            }
        }
        flooor=flooor-1;                   //loop runs largest_num times i.e untill height floor becomes 0
        cout<<endl;                        //end line to print the next floor/ line
    }
}//the functions prints the pattern in a grid of largest_num/floor and total elements. (largest_num X size) grid



// Purpose:Program start here
// Input Parameters: takes input int array until user enters 0
// Output Parameters:Runs function print_function to print output
// Return Value: Always returns 0 if pass

int main() {
    const int MAX_input = 100;
    int a[MAX_input];
    int size= MAX_input;
    for(int i=0;i<MAX_input;i++){
        cin>>a[i];
        if(a[i]==0){
            size=i;                         //getting the value of i to know the size of array. 
            break;
        }
	// if the user added more then 100 numbers then the loop will print first 100 numbers as size is 100.  
    }
    //cout<<size<<endl;
    print_function(a,size);                 //sending array a and size to getting the pattern printed.
    
    //cout<<largest_num<<endl;
    return 0;
}