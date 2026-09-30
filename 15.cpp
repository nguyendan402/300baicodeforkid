#include <iostream>
using namespace std;

int badVersion;   // first bad version, used to simulate the API
int apiCalls = 0; // counts API calls

bool isBadVersion(int version) {
    apiCalls++;
    return version >= badVersion;
}

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2; // avoids overflow
            if (isBadVersion(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};

void runTest(int n, int bad) {
    badVersion = bad;
    apiCalls = 0;
    Solution sol;
    int result = sol.firstBadVersion(n);
    cout << "n = " << n << ", bad = " << bad
         << " -> result: " << result
         << " (API calls: " << apiCalls << ")\n";
}

int main() {
    // Examples from the problem
    runTest(5, 4);
    runTest(1, 1);

    // Maximum value allowed by the constraints: n = 2^31 - 1
    runTest(2147483647, 2147483647);
    runTest(2147483647, 1);
    runTest(2147483647, 1000000000);

    // User input
    int n, bad;
    cout << "\nEnter n and bad: ";
    cin >> n >> bad;
    runTest(n, bad);

    return 0;
}