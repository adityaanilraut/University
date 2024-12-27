#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

int rodCutDP(vector<int>& price, int length) {
    // DP table to store maximum profits
    vector<int> dp(length + 1, 0);
    
    // Build solution bottom-up
    for (int i = 1; i <= length; i++) {
        int maxProfit = INT_MIN;
        
        // Try all possible cuts
        for (int j = 1; j <= i; j++) {
            // Price of current piece + profit from remaining length
            maxProfit = max(maxProfit, price[j-1] + dp[i-j]);
        }
        
        dp[i] = maxProfit;
    }
    
    return dp[length];
}

// Function to reconstruct the actual cuts
vector<int> reconstructCuts(vector<int>& price, int length) {
    vector<int> dp(length + 1, 0);
    vector<int> cuts(length + 1, 0);
    
    for (int i = 1; i <= length; i++) {
        int maxProfit = INT_MIN;
        
        for (int j = 1; j <= i; j++) {
            if (maxProfit < price[j-1] + dp[i-j]) {
                maxProfit = price[j-1] + dp[i-j];
                cuts[i] = j;
            }
        }
        
        dp[i] = maxProfit;
    }
    
    // Trace back the cuts
    vector<int> rodCuts;
    while (length > 0) {
        rodCuts.push_back(cuts[length]);
        length -= cuts[length];
    }
    
    return rodCuts;
}

int main() {
    // Test cases
    vector<pair<int, vector<int>>> testCases = {
        {8, {1, 5, 8, 9, 10, 17, 17, 20}},
        {5, {2, 5, 7, 8, 10}},
        {12, {2, 5, 7, 8, 10,12,15,15,16,17,21,21}},
        {15, {2, 5, 7, 8, 10,12,15,15,16,17,21,21,24,25,26}},
        {20, {2, 5, 7, 8, 10,12,15,15,16,17,21,21,24,25,26,30,34,35,36,37}}
    };
    
    for (auto& testCase : testCases) {
        int rodLength = testCase.first;
        vector<int>& prices = testCase.second;
        
        // Measure execution time
        auto start = high_resolution_clock::now();
        
        // Call dynamic programming function
        int result = rodCutDP(prices, rodLength);
        
        // Get optimal cuts
        vector<int> optimalCuts = reconstructCuts(prices, rodLength);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "Rod Length: " << rodLength << endl;
        cout << "Price Array: ";
        for (int p : prices) cout << p << " ";
        cout << "\nMaximum Profit: " << result;
        cout << "\nOptimal Cuts: ";
        for (int cut : optimalCuts) cout << cut << " ";
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
