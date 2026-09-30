#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Approach 1: two variables, O(n) time, O(1) space
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev = 1, curr = 2; // ways(1), ways(2)
        for (int i = 3; i <= n; i++) {
            int next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }

    // Approach 2: array-based dynamic programming, O(n) time, O(n) space
    int climbStairsDP(int n) {
        if (n <= 2) return n;
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    // Approach 3: recursion with memoization
    int climbStairsMemo(int n) {
        vector<int> memo(n + 1, 0);
        return helper(n, memo);
    }

private:
    int helper(int n, vector<int>& memo) {
        if (n <= 2) return n;
        if (memo[n] != 0) return memo[n];
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo);
        return memo[n];
    }
};

void runTest(int n, int expected) {
    Solution sol;
    int result = sol.climbStairs(n);
    cout << "n = " << n << " -> " << result
         << (result == expected ? "  [PASS]" : "  [FAIL]") << "\n";
}

int main() {
    // Examples from the problem
    runTest(2, 2);
    runTest(3, 3);

    // Edge cases
    runTest(1, 1);
    runTest(4, 5);
    runTest(5, 8);
    runTest(10, 89);

    // Maximum value allowed by the constraints
    runTest(45, 1836311903);

    // Compare all 3 approaches for every n from 1 to 45
    Solution sol;
    bool allMatch = true;
    for (int n = 1; n <= 45; n++) {
        int a = sol.climbStairs(n);
        int b = sol.climbStairsDP(n);
        int c = sol.climbStairsMemo(n);
        if (a != b || b != c) {
            cout << "Mismatch at n = " << n << ": " << a << ", " << b << ", " << c << "\n";
            allMatch = false;
        }
    }
    cout << "\nComparing 3 approaches for n = 1..45: "
         << (allMatch ? "[PASS] all match" : "[FAIL]") << "\n";

    // User input
    int n;
    cout << "\nEnter n (1 <= n <= 45): ";
    cin >> n;
    if (n < 1 || n > 45) {
        cout << "n is outside the allowed range.\n";
        return 1;
    }
    cout << "Result: " << sol.climbStairs(n) << "\n";

    return 0;
}