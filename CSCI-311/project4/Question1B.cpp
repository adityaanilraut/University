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

int matrixChainDP(vector<int>& p) {
    int n = p.size() - 1;
    
    // Create DP table to store minimum scalar multiplications
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    // Iterate over different chain lengths
    for (int chainLen = 2; chainLen <= n; chainLen++) {
        for (int i = 1; i <= n - chainLen + 1; i++) {
            int j = i + chainLen - 1;
            
            // Initialize to a large value
            dp[i][j] = INT_MAX;
            
            // Try all possible split points
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + p[i-1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    // Return minimum scalar multiplications for entire chain
    return dp[1][n];
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
        
        
        int result = matrixChainDP(p);
        
        
        
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
