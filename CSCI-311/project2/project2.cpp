#include<iostream>
#include<chrono>
#include<random>
#include<algorithm>
#include <array>
#include <fstream>
using namespace std;
void printArray(int arr[], int size) {
for (int i = 0; i < size; i++) {
cout << arr[i] << " ";
}
cout << endl;
}
vector < int > arrGen(int size){
    random_device rd ;
    mt19937 mt (rd()) ;
    uniform_int_distribution < int > dist (1 , 1000) ;
    vector < int > v (size);
    for ( int i = 0; i <size ; i ++) {
    v [ i ] = dist ( mt ) ;
    }
    return v;

}
float bubbleSort(vector < int > arr,int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    int i = n;
    while(i>0)
    {
        //printArray(arr,8);
        bool isSwap=false;
        int j=0;
        /*
        Once the window has been placed, if it is within the valid bounds of j=0 to j=i-2
        then the swap is allowed. If the window is placed starting at j=i-1 then the swap is not
        allowed and the loop breaks. 
        */
        while(j<i-1)
        {
            if (arr[j]>arr[j+1])
            {
                isSwap=true;
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
            j++;
        }

        //j=i-1;  invalid bound of the window. 
        if (!isSwap)
            break;
        i=i-1;
}
//i=0
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}
float insertionSort(vector < int > arr,int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    int i=1;
    while(i<n)
    {
        //printArray(arr,8);   
        int key=arr[i];
        int j=i-1;
        while(j>=0)
        {
            //printArray(arr,8);
            if (arr[j]>key)
            {
                arr[j+1]=arr[j];
                j=j-1;
            }
            else
            {
                break;
            }
        }   
        arr[j+1]=key;     
        //j=-1;
        i++;
    }
//i=0
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}


float selectionSort(vector < int > &arr,int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    int i=-1; //i is keeping track of the start of the sorted array
    while(i<n-1)
    {
        //printArray(arr,4);
        int bestMinIndexSoFar = i+1;
        int j=i+2;
        while(j<n)
        {
            if (arr[j]<arr[bestMinIndexSoFar])
            {
                bestMinIndexSoFar=j;
            }
            j=j+1;
        }
        //j = n 

        int temp = arr[bestMinIndexSoFar];
        arr[bestMinIndexSoFar]=arr[i+1];
        arr[i+1]=temp;
        i++;
        
    }
    //i=n-1
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}

void merge(vector < int > &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    int i = 0;
    while (i < n1) {
        L[i] = arr[l + i];
        i++;
    }
    int j = 0;
    while (j < n2) {
        R[j] = arr[m + 1 + j];
        j++;
    }

    // Merge the temp arrays back into arr[l..r]
    i = 0;
    j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector < int > &arr, int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
float mergetime(vector < int > arr,int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}
float methodsort(vector < int > arr,int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}


int partitionNew(int arr[], int low, int high)
{
    // Randomly choose a pivot
    int randomIndex = rand() % ((high - low) + 1);
    int pivot = arr[randomIndex + low];
    cout << pivot << endl;
    int j = low;
    int k = high + 1;
    int i = low;
    while (j < k)
    {
        if (arr[j] == pivot)
        {
            j++;
        }
        else if (arr[j] < pivot)
        {
            swap(arr[j], arr[i]);
            i++;
            j++;
        }
        else
        {
            swap(arr[k - 1], arr[j]);
            k--;
        }
    }
    return i;
}

/*
Worst case T(n) = T(n-1) + n
escribes the worst-case scenario for QuickSort when a deterministic strategy is used,
like always selecting the first element or the last element as the pivot, and the input list
is already sorted (or reverse sorted). I
*/
void quickSortRandomPivot(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionNew(arr, low, high);

        quickSortRandomPivot(arr, low, pi - 1);
        quickSortRandomPivot(arr, pi + 1, high);
    }
}

// Helper function to find the median of five numbers
int medianOfFive(int arr[], int start)
{
    sort(arr + start, arr + start + 5);
    return arr[start + 2];
}

/*
T(n) = T(n/5) + n
*/
int medianOfMedians(int arr[], int low, int high)
{
    int n = high - low + 1;
    int medians[(n + 4) / 5];
    int i;
    for (i = 0; i < n / 5; i++)
    {
        medians[i] = medianOfFive(arr, low + i * 5);
    }
    if (i * 5 < n)
    {
        sort(arr + low + i * 5, arr + high + 1);
        // medians[i] = arr[low + i * 5 + ((high - (low + i * 5)) / 2)];
        medians[i] = arr[low + i * 5];
        i++;
    }
    if (i == 1)
        return medians[0];
    else
        return medianOfMedians(medians, 0, i - 1);
}

/*
T(n) = n
*/

int partitionWithGivenPivotNew(int arr[], int low, int high, int pivot)
{
    int j = low;
    int k = high + 1;
    int i = low;
    while (j < k)
    {
        if (arr[j] == pivot)
        {
            j++;
        }
        else if (arr[j] < pivot)
        {
            swap(arr[j], arr[i]);
            i++;
            j++;
        }
        else
        {
            swap(arr[k - 1], arr[j]);
            k--;
        }
    }
    return i;
}

/*
T(n) = n + T(3n/10)+T(7n/10)

*/
void quickSortMedianOfMedians(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotValue = medianOfMedians(arr, low, high);
        int pi = partitionWithGivenPivotNew(arr, low, high, pivotValue);

        quickSortMedianOfMedians(arr, low, pi - 1);
        quickSortMedianOfMedians(arr, pi + 1, high);
    }
}


float quicksort(int arr[],int n)
{   chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();
    quickSortMedianOfMedians(arr, 0, n);
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    return duration.count();
}



int main(){

    chrono::high_resolution_clock::time_point start=chrono::
    high_resolution_clock::now();

    ofstream file("new.csv");
    if (!file) { // Check if file opened successfully
        cerr << "File not found" <<endl;
        return 1;
    }

    
    
    
    vector < int > v;
    vector < int > v2;
    vector < int > v3;
    vector < int > v4;
    vector < int > v5;
   
    int j=10000;
    float a1,b1,c1,d1,e1,zz;
    file<<"size"<<","<<"bubbleSort"<<","<<"insertionSort"<<","<<"selectionSort"<<","<<"mergesort"<<","<<"quicksort"<<","<<"methodsort"<<endl;
    for(int i=0;i<1;i=i+1){
        j=100000;
        
        v =arrGen(j);
        if (i<500){
            sort(v.begin(), v.end());
        }

        if (i>500){
            sort(v.begin(), v.end());
            for(int r=0;r<500;r++){
                swap(v[r],v[1000-r]);
            }
        }
        
        v2=v;
        v3=v;
        v4=v;
        v5=v;
        int newarr[j];
        copy(v.begin(), v.end(), newarr);


        a1=bubbleSort(v,j);
        b1=insertionSort(v2,j);
        c1=selectionSort(v3,j);
        d1=mergetime(v4,j);
        e1=quicksort(newarr,j);
        zz=methodsort(v5,j);

        
        if (a1>0 && b1>0 && c1>0 && d1>0 && e1>0 && zz>0){
            //cout<<"printing";
            file<<i<<","<<a1<<","<<b1<<","<<c1<<","<<d1<<","<<e1<<","<<zz<<endl;
        }
        
    }
    





    //int arr[]={64,32,12,0,-1,10,25,-4};
    //int size = sizeof(arr)/sizeof(int);
    //cout<<bubbleSort(v,size)<<endl;
    //insertionSort(arr,size);
    //printArray(v,8);
    //cout<<"hello"<<endl;
    chrono::high_resolution_clock::time_point end=chrono::
    high_resolution_clock::now();
    chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
    double > >( end - start ) ;
    file<<duration.count()<<endl;
    return 0;
}



///Users/aditya/Desktop/project 2/jupyter.ipynb