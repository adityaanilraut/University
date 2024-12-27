#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool canPartitionNaive(vector<int>& nums, int index, int subset1Sum, int subset2Sum) {
    // Base case: reached end of array
    if (index == nums.size()) {
        // Check if the two subsets have equal sum
        return subset1Sum == subset2Sum;
    }
    

    bool option1 = canPartitionNaive(nums, index + 1, subset1Sum + nums[index], subset2Sum);
    

    bool option2 = canPartitionNaive(nums, index + 1, subset1Sum, subset2Sum + nums[index]);
    

    bool option3 = canPartitionNaive(nums, index + 1, subset1Sum, subset2Sum);
    
    // Return true if any option leads to equal subset sums
    return option1 || option2 || option3;
}

bool canPartition(vector<int>& nums) {
    // Total sum must be even to have equal partition
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    if (totalSum % 2 != 0) return false;
    
    // Start recursive search
    return canPartitionNaive(nums, 0, 0, 0);
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
        
        // Call naive recursive function
        bool result = canPartition(nums);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "Input: ";
        for (int x : nums) cout << x << " ";
        cout << "\nCan be partitioned equally: " << (result ? "True" : "False");
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
