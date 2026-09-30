#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> count(26, 0);
        for (char c : magazine) {
            count[c - 'a']++;
        }
        for (char c : ransomNote) {
            if (--count[c - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }
};

void runTest(const string& ransomNote, const string& magazine, bool expected) {
    Solution sol;
    bool result = sol.canConstruct(ransomNote, magazine);

    // For long strings, print only the lengths to keep the output short
    if (ransomNote.size() <= 20 && magazine.size() <= 20) {
        cout << "ransomNote = \"" << ransomNote << "\", magazine = \"" << magazine << "\"";
    } else {
        cout << "ransomNote (len " << ransomNote.size() << "), magazine (len "
             << magazine.size() << ")";
    }
    cout << " -> " << (result ? "true" : "false")
         << (result == expected ? "  [PASS]" : "  [FAIL]") << "\n";
}

int main() {
    // Examples from the problem
    runTest("a", "b", false);
    runTest("aa", "ab", false);
    runTest("aa", "aab", true);

    // Edge cases
    runTest("a", "a", true);
    runTest("abc", "abc", true);
    runTest("abc", "cba", true);
    runTest("abc", "ab", false);
    runTest("z", "abcdefghijklmnopqrstuvwxy", false);

    // Large tests per the constraints: length 10^5
    runTest(string(100000, 'a'), string(100000, 'a'), true);
    runTest(string(100000, 'a'), string(99999, 'a'), false);

    // User input
    string ransomNote, magazine;
    cout << "\nEnter ransomNote: ";
    cin >> ransomNote;
    cout << "Enter magazine: ";
    cin >> magazine;
    Solution sol;
    cout << "Result: " << (sol.canConstruct(ransomNote, magazine) ? "true" : "false") << "\n";

    return 0;
}