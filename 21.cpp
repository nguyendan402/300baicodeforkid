/*
 * Add Binary
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * Example 1:
 *   Input: a = "11", b = "1"
 *   Output: "100"
 *
 * Example 2:
 *   Input: a = "1010", b = "1011"
 *   Output: "10101"
 *
 * Constraints:
 *   1 <= a.length, b.length <= 10^4
 *   a and b consist only of '0' or '1' characters.
 *   Each string does not contain leading zeros except for the zero itself.
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Add from the least significant digit, carrying as we go
    // Time: O(max(n, m)), Space: O(max(n, m)) for the result
    string addBinary(string a, string b) {
        string res;
        int i = (int)a.size() - 1, j = (int)b.size() - 1, carry = 0;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            res.push_back('0' + (sum & 1));  // current bit
            carry = sum >> 1;                // carry to the next bit
        }
        // Bits were built from least to most significant, so reverse them
        reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Solution sol;

    // Example 1
    string a1 = "11", b1 = "1";
    cout << "Example 1" << endl;
    cout << "Input: a = \"" << a1 << "\", b = \"" << b1 << "\"" << endl;
    cout << "Output: \"" << sol.addBinary(a1, b1) << "\"" << endl;  // "100"

    // Example 2
    string a2 = "1010", b2 = "1011";
    cout << "\nExample 2" << endl;
    cout << "Input: a = \"" << a2 << "\", b = \"" << b2 << "\"" << endl;
    cout << "Output: \"" << sol.addBinary(a2, b2) << "\"" << endl;  // "10101"

    // Custom input
    string a, b;
    cout << "\nEnter binary string a: ";
    cin >> a;
    cout << "Enter binary string b: ";
    cin >> b;
    cout << "Output: \"" << sol.addBinary(a, b) << "\"" << endl;
    return 0;
}