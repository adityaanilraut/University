#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool canPartitionDP(vector<int>& nums) {
    // Total sum must be even to have equal partition
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if (totalSum % 2 != 0) return false;
    
    int targetSum = totalSum / 2;
    int n = nums.size();
    
    // DP table to track possible subset sums
    vector<bool> dp(targetSum + 1, false);
    
    // 0 sum is always possible
    dp[0] = true;
    
    // Build solution bottom-up
    for (int num : nums) {
        // Iterate backwards to avoid using same element multiple times
        for (int j = targetSum; j >= num; j--) {
            dp[j] = dp[j] or dp[j - num];

        }
    }
    
    return dp[targetSum];
}

// Function to reconstruct the actual partition
vector<vector<int>> reconstructPartition(vector<int>& nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if (totalSum % 2 != 0) return {};
    
    int targetSum = totalSum / 2;
    int n = nums.size();
    
    // 2D DP table to track possible subset sums and used elements
    vector<vector<bool>> dp(n + 1, vector<bool>(targetSum + 1, false));
    
    // 0 sum is always possible
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }
    
    // Build solution bottom-up
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= targetSum; j++) {
            if (j >= nums[i-1]) {
                dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i-1]];
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    // If no partition possible
    if (!dp[n][targetSum]) return {};
    
    // Reconstruct the partition
    vector<int> subset1, subset2;
    int j = targetSum;
    for (int i = n; i > 0 && j > 0; i--) {
        if (!dp[i-1][j]) {
            subset1.push_back(nums[i-1]);
            j -= nums[i-1];
        } else {
            subset2.push_back(nums[i-1]);
        }
    }
    
    return {subset1, subset2};
}

int main() {
    // Test cases
    vector<vector<int>> testCases = {
        {1, 5, 11, 5},
        {1, 2, 3, 5},
        {2, 3, 5},
        {2, 5, 7, 8, 10,12,15,15,16,17,21,21,24,25,26,30,34,35,36,37}
    };
    
    for (auto& nums : testCases) {
        // Measure execution time
        auto start = high_resolution_clock::now();
        
        // Call dynamic programming function
        bool result = canPartitionDP(nums);
        
        // Attempt to reconstruct partition
        vector<vector<int>> partitions = reconstructPartition(nums);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "Input: ";
        for (int x : nums) cout << x << " ";
        cout << "\nCan be partitioned equally: " << (result ? "True" : "False");
        
        if (result) {
            cout << "\nPartitions:";
            for (const auto& subset : partitions) {
                cout << "\n  [";
                for (int x : subset) cout << x << " ";
                cout << "]";
            }
        }
        
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
