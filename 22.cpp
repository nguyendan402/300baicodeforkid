/*
 * 543. Diameter of Binary Tree
 * Easy
 *
 * Given the root of a binary tree, return the length of the diameter of the tree.
 *
 * The diameter of a binary tree is the length of the longest path between
 * any two nodes in a tree. This path may or may not pass through the root.
 *
 * The length of a path between two nodes is represented by the number of
 * edges between them.
 *
 * Example 1:
 *   Input: root = [1,2,3,4,5]
 *   Output: 3
 *   Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
 *
 * Example 2:
 *   Input: root = [1,2]
 *   Output: 1
 *
 * Constraints:
 *   The number of nodes in the tree is in the range [1, 10^4].
 *   -100 <= Node.val <= 100
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // The longest path through a node = height(left) + height(right).
    // Track the maximum over all nodes while computing heights.
    // Time: O(n), Space: O(h) for the recursion stack
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }

private:
    // Returns the height of the subtree, updates diameter (in edges)
    int height(TreeNode* node, int& diameter) {
        if (!node) return 0;
        int l = height(node->left, diameter);
        int r = height(node->right, diameter);
        diameter = max(diameter, l + r);
        return 1 + max(l, r);
    }
};

const int NIL = INT_MIN;  // marks a null node in the level-order input

// Build a tree from a level-order vector (LeetCode style)
TreeNode* buildTree(const vector<int>& v) {
    if (v.empty() || v[0] == NIL) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < v.size()) {
        TreeNode* cur = q.front();
        q.pop();
        if (i < v.size() && v[i] != NIL) {
            cur->left = new TreeNode(v[i]);
            q.push(cur->left);
        }
        i++;
        if (i < v.size() && v[i] != NIL) {
            cur->right = new TreeNode(v[i]);
            q.push(cur->right);
        }
        i++;
    }
    return root;
}

// Free the tree's memory
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    Solution sol;

    // Example 1
    TreeNode* t1 = buildTree({1, 2, 3, 4, 5});
    cout << "Example 1" << endl;
    cout << "Input: root = [1,2,3,4,5]" << endl;
    cout << "Output: " << sol.diameterOfBinaryTree(t1) << endl;  // 3
    freeTree(t1);

    // Example 2
    TreeNode* t2 = buildTree({1, 2});
    cout << "\nExample 2" << endl;
    cout << "Input: root = [1,2]" << endl;
    cout << "Output: " << sol.diameterOfBinaryTree(t2) << endl;  // 1
    freeTree(t2);

    // Custom input: first n, then n tokens in level-order (write "null" for a missing node)
    int n;
    cout << "\nEnter n (number of entries in level-order): ";
    if (cin >> n && n > 0) {
        cout << "Enter " << n << " values (use null for a missing node): ";
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            v[i] = (s == "null") ? NIL : stoi(s);
        }
        TreeNode* t = buildTree(v);
        cout << "Output: " << sol.diameterOfBinaryTree(t) << endl;
        freeTree(t);
    }
    return 0;
}