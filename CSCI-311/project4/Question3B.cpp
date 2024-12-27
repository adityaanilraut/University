#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;


bool wordBreakDP(const string& s, const unordered_set<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    
   
    int maxWordLen = 0;
    for (const auto& word : wordDict) {
        maxWordLen = max(maxWordLen, (int)word.length());
    }
    
    // Optimized DP approach
    for (int i = 1; i <= n; i++) {

        for (int len = 1; len <= min(i, maxWordLen); len++) {
            if (dp[i - len]) {
      
                string_view potential(s.data() + i - len, len);
                if (wordDict.find(string(potential)) != wordDict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }
    
    return dp[n];
}


vector<string> reconstructWordBreak(const string& s, const unordered_set<string>& wordDict) {
    int n = s.length();
    vector<bool> dp(n + 1, false);
    vector<int> prevBreak(n + 1, -1);
    dp[0] = true;
    
    // Find maximum word length
    int maxWordLen = 0;
    for (const auto& word : wordDict) {
        maxWordLen = max(maxWordLen, (int)word.length());
    }
    
    // Optimized reconstruction
    for (int i = 1; i <= n; i++) {
        for (int len = 1; len <= min(i, maxWordLen); len++) {
            if (dp[i - len]) {
                string_view potential(s.data() + i - len, len);
                if (wordDict.find(string(potential)) != wordDict.end()) {
                    dp[i] = true;
                    prevBreak[i] = i - len;
                    break;
                }
            }
        }
    }
    
    if (!dp[n]) return {};
    
    vector<string> segmentation;
    int curr = n;
    while (curr > 0) {
        int prev = prevBreak[curr];
        segmentation.insert(segmentation.begin(), string(s.data() + prev, curr - prev));
        curr = prev;
    }
    
    return segmentation;
}

int main() {
    // Test cases 
    vector<pair<string, vector<string>>> testCases = {
        {"vdsghajfghjvwefdbwbejherekqehnqwfkjqwhruyqwgtfhvcb mndsd xnams qhjwegfuywqefvbhjwcb nwmcwjhqecvbwhjqcvwcpplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapplepenapple", {"apple", "pen"}},
        {"catsandogcats", {"cats", "dog", "sand", "and", "cat"}}

    };
    
    for (const auto& testCase : testCases) {
        const string& s = testCase.first;
        unordered_set<string> wordDict(testCase.second.begin(), testCase.second.end());
        
        auto start = high_resolution_clock::now();
        bool result = wordBreakDP(s, wordDict);
        vector<string> segmentation = reconstructWordBreak(s, wordDict);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        
        cout << "String: " << s << endl;
        cout << "Dictionary: ";
        for (const string& word : wordDict) cout << word << " ";
        cout << "\nCan be segmented: " << (result ? "True" : "False");
        
        if (result) {
            cout << "\nSegmentation: ";
            for (const string& word : segmentation) cout << word << " ";
        }
        
        cout << "\nExecution time: " << duration.count() << " microseconds\n\n";
    }
    
    return 0;
}