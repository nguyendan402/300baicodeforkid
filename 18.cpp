#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    // Approach 1: count array, O(n) time, O(1) space
    int longestPalindrome(string s) {
        vector<int> count(128, 0); // ASCII, case sensitive
        for (char c : s) {
            count[(int)c]++;
        }
        int length = 0;
        bool hasOdd = false;
        for (int c : count) {
            length += c / 2 * 2; // use all pairs
            if (c % 2 == 1) hasOdd = true;
        }
        return hasOdd ? length + 1 : length;
    }

    // Approach 2: toggle set, letters left in the set have an odd count
    int longestPalindromeSet(string s) {
        unordered_set<char> odd;
        for (char c : s) {
            if (odd.count(c)) odd.erase(c);
            else odd.insert(c);
        }
        int n = (int)s.size();
        if (odd.empty()) return n;
        return n - (int)odd.size() + 1;
    }
};

// Approach 3: actually build a longest palindrome
string buildPalindrome(const string& s) {
    vector<int> count(128, 0);
    for (char c : s) count[(int)c]++;

    string half, middle;
    for (int ch = 0; ch < 128; ch++) {
        half += string(count[ch] / 2, (char)ch);
        if (count[ch] % 2 == 1 && middle.empty()) {
            middle = string(1, (char)ch);
        }
    }
    string rev(half.rbegin(), half.rend());
    return half + middle + rev;
}

// Checks that p is a palindrome and only uses letters available in s
bool isValidPalindromeFrom(const string& p, const string& s) {
    string rev(p.rbegin(), p.rend());
    if (p != rev) return false;
    vector<int> count(128, 0);
    for (char c : s) count[(int)c]++;
    for (char c : p) {
        if (--count[(int)c] < 0) return false;
    }
    return true;
}

void runTest(const string& s, int expected) {
    Solution sol;
    int a = sol.longestPalindrome(s);
    int b = sol.longestPalindromeSet(s);
    string built = buildPalindrome(s);
    bool ok = (a == expected) && (b == expected)
              && ((int)built.size() == expected)
              && isValidPalindromeFrom(built, s);

    if (s.size() <= 20) {
        cout << "s = \"" << s << "\"";
    } else {
        cout << "s (len " << s.size() << ")";
    }
    cout << " -> " << a;
    if (built.size() <= 20) cout << ", palindrome: \"" << built << "\"";
    cout << (ok ? "  [PASS]" : "  [FAIL]") << "\n";
}

int main() {
    // Examples from the problem
    runTest("abccccdd", 7);
    runTest("a", 1);

    // Edge cases
    runTest("Aa", 1);        // case sensitive
    runTest("AAaa", 4);
    runTest("aaa", 3);
    runTest("abc", 1);
    runTest("aabb", 4);
    runTest("aaabbb", 5);

    // Large tests per the constraints: length 2000
    runTest(string(2000, 'a'), 2000);
    string alt;
    for (int i = 0; i < 1000; i++) alt += "aB";
    runTest(alt, 2000);
    runTest("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 1);

    // Random tests: compare all 3 approaches
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    mt19937 rng(12345);
    Solution sol;
    bool allMatch = true;
    for (int t = 0; t < 2000; t++) {
        int len = uniform_int_distribution<int>(1, 2000)(rng);
        int alphabet = uniform_int_distribution<int>(1, 52)(rng);
        string s;
        for (int i = 0; i < len; i++) {
            s += letters[uniform_int_distribution<int>(0, alphabet - 1)(rng)];
        }
        int a = sol.longestPalindrome(s);
        int b = sol.longestPalindromeSet(s);
        string built = buildPalindrome(s);
        if (a != b || (int)built.size() != a || !isValidPalindromeFrom(built, s)) {
            cout << "Mismatch on a random test (len " << len << ")\n";
            allMatch = false;
            break;
        }
    }
    cout << "\nRandom tests (2000 cases): "
         << (allMatch ? "[PASS] all approaches agree" : "[FAIL]") << "\n";

    // User input
    string s;
    cout << "\nEnter s (1 <= length <= 2000, letters only): ";
    cin >> s;
    if (s.empty() || s.size() > 2000
        || !all_of(s.begin(), s.end(), [](unsigned char c) { return isalpha(c); })) {
        cout << "Input is outside the allowed constraints.\n";
        return 1;
    }
    cout << "Result: " << sol.longestPalindrome(s) << "\n";
    cout << "One such palindrome: " << buildPalindrome(s) << "\n";

    return 0;
}