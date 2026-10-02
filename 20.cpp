/*
 * Majority Element
 *
 * Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than floor(n / 2) times.
 * You may assume that the majority element always exists in the array.
 *
 * Example 1: nums = [3,2,3]         -> 3
 * Example 2: nums = [2,2,1,1,1,2,2] -> 2
 *
 * Constraints:
 *   n == nums.length
 *   1 <= n <= 5 * 10^4
 *   -10^9 <= nums[i] <= 10^9
 *
 * Follow-up: solve it in linear time and O(1) space.
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Boyer-Moore Voting Algorithm: O(n) time, O(1) space
    int majorityElement(vector<int>& nums) {
        int candidate = 0, count = 0;
        for (int x : nums) {
            // When the count drops to zero, pick a new candidate
            if (count == 0) candidate = x;
            // Same as candidate: vote for it, otherwise vote against it
            count += (x == candidate) ? 1 : -1;
        }
        // The majority element is guaranteed to exist, so no second pass is needed
        return candidate;
    }
};

int main() {
    Solution sol;

    // Built-in examples
    vector<int> a = {3, 2, 3};
    vector<int> b = {2, 2, 1, 1, 1, 2, 2};
    cout << "Example 1: " << sol.majorityElement(a) << endl;  // 3
    cout << "Example 2: " << sol.majorityElement(b) << endl;  // 2

    // Custom input: first n, then n integers
    int n;
    cout << "\nEnter n: ";
    if (cin >> n && n > 0) {
        vector<int> nums(n);
        cout << "Enter " << n << " integers: ";
        for (int i = 0; i < n; i++) cin >> nums[i];
        cout << "Majority element: " << sol.majorityElement(nums) << endl;
    }
    return 0;
}