#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to check if a substring is a palindrome
bool isPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

// Naive recursive solution to find minimum cuts
int minCutNaive(string s, int start, int end) {
    // Base cases
    // If substring is empty or single character, no cuts needed
    if (start >= end || isPalindrome(s, start, end)) {
        return 0;
    }
    
    int minCuts = INT_MAX;
    
    // Try all possible cuts
    for (int k = start; k < end; k++) {
        // Only consider if left part is palindrome
        if (isPalindrome(s, start, k)) {
            int currentCuts = 1 + minCutNaive(s, k + 1, end);
            minCuts = min(minCuts, currentCuts);
        }
    }
    
    return minCuts;
}

int main() {
    // Test cases
    vector<string> testCases = {
         "racecardkahudhiuahdjkahsjasjjjsjsjsjjsahsduyajhcbna",
        "noonabbaddhuwfhjkqhdbhjsabduyagdsajdhsjdajksdhjkasiiiiiiiiiiuyagdsajdhsjdajksdhjkasi",
        "bananaagsdykuatefgjahefhsjdhshhhhhhahefhsjdhshhh"//"racecar",
       // "noonabbad",
       // "banana"
    };
    
    for (const string& s : testCases) {
        // Measure execution time
        auto start = high_resolution_clock::now();
        
        // Call naive recursive function
        int result = minCutNaive(s, 0, s.length() - 1);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "String: " << s;
        cout << "\nMinimum cuts: " << result;
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
