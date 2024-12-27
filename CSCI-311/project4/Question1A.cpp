#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include<random>
using namespace std;
using namespace std::chrono;
vector < int > arrGen(int size){
    random_device rd ;
    mt19937 mt (rd()) ;
    uniform_int_distribution < int > dist (10 , 99) ;
    vector < int > v (size);
    for ( int i = 0; i <size ; i ++) {
    v [ i ] = dist ( mt ) ;
    }
    return v;

}

int matrixChainNaive(vector<int>& p, int i, int j) {
    // Base case: if only one matrix, no multiplication needed
    if (i == j) {
        return 0;
    }
    
    // Initialize minimum cost to a large value
    int minCost = INT_MAX;
    
    // Try all possible split points between i and j
    for (int k = i; k < j; k++) {
        // Calculate cost of current split
        int cost = matrixChainNaive(p, i, k) + 
                   matrixChainNaive(p, k + 1, j) + 
                   p[i-1] * p[k] * p[j];
        
        // Update minimum cost if current cost is less
        minCost = min(minCost, cost);
    }
    
    return minCost;
}

int main() {
    // Test cases
    int size=1;
        
    //vector<vector<int>> v =arrGen(j);

    vector<vector<int>> testCases = {
        {10, 20, 30, 40, 30},
        {30, 35, 15, 5, 10, 20, 25},
        {5, 10, 3, 12, 5, 50, 6}
 
    };
    for(int j=10;j<20;j=j+1){
        
        testCases.push_back(arrGen(j));
        size=size+1;
    }
    
    
    for (auto& p : testCases) {
        
        chrono::high_resolution_clock::time_point start=chrono::
        high_resolution_clock::now();
        
        
        int result = matrixChainNaive(p, 1, p.size() - 1);
        
        
        
        //cout << "Input: ";
        //for (int x : p) cout << x << " ";
        //cout << "\nMinimum scalar multiplications: " << result;
        //cout << "\nExecution time: " << duration.count() << " microseconds\n\n";

        chrono::high_resolution_clock::time_point end=chrono::
        high_resolution_clock::now();
        chrono :: duration <double > duration = chrono :: duration_cast < chrono :: duration <
        double > >( end - start );
        cout<<duration.count()<<endl;
    }
    
    return 0;
}
