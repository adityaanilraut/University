#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

int minCutDP(string s) {
    int n = s.length();
    
    // DP table to track palindrome status
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
    
    // DP table to track minimum cuts
    vector<int> cuts(n);
    
    // All single characters are palindromes
    for (int i = 0; i < n; i++) {
        isPalindrome[i][i] = true;
    }
    
    // Check palindromes of length 2 to n
    for (int len = 2; len <= n; len++) {
        for (int start = 0; start < n - len + 1; start++) {
            int end = start + len - 1;
            
            // Palindrome if length is 2 or characters match and inner substring is palindrome
            if (len == 2) {
                isPalindrome[start][end] = (s[start] == s[end]);
            } else {
                isPalindrome[start][end] = (s[start] == s[end]) && isPalindrome[start+1][end-1];
            }
        }
    }
    
    // Compute minimum cuts
    for (int end = 0; end < n; end++) {
        // If entire substring is palindrome, no cuts needed
        if (isPalindrome[0][end]) {
            cuts[end] = 0;
        } else {
            cuts[end] = INT_MAX;
            for (int k = 0; k < end; k++) {
                if (isPalindrome[k+1][end]) {
                    cuts[end] = min(cuts[end], cuts[k] + 1);
                }
            }
        }
    }
    
    return cuts[n-1];
}

// Function to reconstruct the actual palindrome partitioning
vector<vector<string>> reconstructPartition(string s) {
    int n = s.length();
    
    // DP table to track palindrome status
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
    
    // DP table to track minimum cuts
    vector<int> cuts(n);
    
    // All single characters are palindromes
    for (int i = 0; i < n; i++) {
        isPalindrome[i][i] = true;
    }
    
    // Check palindromes of length 2 to n
    for (int len = 2; len <= n; len++) {
        for (int start = 0; start < n - len + 1; start++) {
            int end = start + len - 1;
            
            // Palindrome if length is 2 or characters match and inner substring is palindrome
            if (len == 2) {
                isPalindrome[start][end] = (s[start] == s[end]);
            } else {
                isPalindrome[start][end] = (s[start] == s[end]) && isPalindrome[start+1][end-1];
            }
        }
    }
    
    // Compute minimum cuts and track partitions
    vector<vector<string>> partitions(n);
    for (int end = 0; end < n; end++) {
        // If entire substring is palindrome, no cuts needed
        if (isPalindrome[0][end]) {
            cuts[end] = 0;
            partitions[end] = {s.substr(0, end + 1)};
        } else {
            cuts[end] = INT_MAX;
            for (int k = 0; k < end; k++) {
                if (isPalindrome[k+1][end]) {
                    int currentCuts = cuts[k] + 1;
                    if (currentCuts < cuts[end]) {
                        cuts[end] = currentCuts;
                        
                        // Reconstruct partition
                        if (k >= 0) {
                            partitions[end] = partitions[k];
                        }
                        partitions[end].push_back(s.substr(k+1, end - k));
                    }
                }
            }
        }
    }
    
    return {partitions[n-1]};
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
        
        // Call dynamic programming function
        int result = minCutDP(s);
        
        // Reconstruct palindrome partitioning
        vector<vector<string>> partitions = reconstructPartition(s);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "String: " << s;
        cout << "\nMinimum cuts: " << result;
        
        // Display partitions
        cout << "\nPalindrome Partitions:";
        for (const auto& partition : partitions) {
            cout << "\n  [";
            for (const string& p : partition) {
                cout << p << " ";
            }
            cout << "]";
        }
        
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
