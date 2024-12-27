#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

int rodCutNaive(vector<int>& price, int length) {
    // Base case: if length is 0, no profit
    if (length <= 0) {
        return 0;
    }
    
    int maxProfit = INT_MIN;
    
    // Try cutting the rod at every possible length
    for (int i = 1; i <= length; i++) {
        // Current piece's price + profit from remaining length
        int currentProfit = price[i-1] + rodCutNaive(price, length - i);
        maxProfit = max(maxProfit, currentProfit);
    }
    
    return maxProfit;
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
        
        // Call naive recursive function
        int result = rodCutNaive(prices, rodLength);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "Rod Length: " << rodLength << endl;
        cout << "Price Array: ";
        for (int p : prices) cout << p << " ";
        cout << "\nMaximum Profit: " << result;
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
