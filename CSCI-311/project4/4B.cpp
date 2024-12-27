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
    uniform_int_distribution < int > dist (10 , 50) ;
    vector < int > v (size);
    for ( int i = 0; i <size ; i ++) {
    v [ i ] = dist ( mt ) ;
    }
    return v;

}

bool canPartition( vector<int>& nums) {
    int totalSum = 0;
    for (int num : nums) totalSum += num;

    // If total sum is odd, partition is not possible
    if (totalSum % 2 != 0) return false;

    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);

    dp[0] = true; // Base case: sum of 0 is always achievable
    for (int num : nums) {
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
}

int main() {
     vector<vector<int>> testCases = {
        {1, 5, 11, 5},
        {1, 2, 3, 5},
        {2, 3, 5},
        {2, 5, 7, 8, 10,12,15,15,16,17,21,21,24,25,26,30,34,35,36,37}
    };
    for(int j=10;j<50;j=j+1){
        
        testCases.push_back(arrGen(j));
        
    }
    

    for (auto& p : testCases) {
        
        chrono::high_resolution_clock::time_point start=chrono::
        high_resolution_clock::now();
        
        
        bool a =canPartition(p);
        
        
        
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
    ///cout << (canPartition(nums) ? "True" : "False") << endl;
    return 0;
}
