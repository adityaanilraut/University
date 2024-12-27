#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool wordBreakNaive(string s, unordered_set<string> wordDict) {
    // Base case:
    if (s.empty()) {
        return true;
    }
    

    for (int i = 1; i <= s.length(); i++) {
       
        string prefix = s.substr(0, i);
        if (wordDict.count(prefix) > 0) {
     
            string remaining = s.substr(i);
            
     
            if (wordBreakNaive(remaining, wordDict)) {
                return true;
            }
        }
    }
    
   
    return false;
}

int main() {
    // Test cases
     vector<pair<string, vector<string>>> testCases = {
        {"vdsghajfghjvwefdbwbejherekqehnqwfkjqwhruyqwgtfhvcb mndsd xnams qhjwegfuywqefvbhjwcb nwmcwjhqecvbwhjqcvwcpplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapple", {"apple", "pen"}},
        {"catsandogcats", {"cats", "dog", "sand", "and", "cat"}}
       
    };
    
    for (auto& testCase : testCases) {
        string s = testCase.first;
        unordered_set<string> wordDict(testCase.second.begin(), testCase.second.end());
        
        // Measure execution time
        auto start = high_resolution_clock::now();
        
        
        bool result = wordBreakNaive(s, wordDict);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "String: " << s << endl;
        cout << "Dictionary: ";
        for (const string& word : wordDict) cout << word << " ";
        cout << "\nCan be segmented: " << (result ? "True" : "False");
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}
