#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> val = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };
        int total = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (i + 1 < n && val[s[i]] < val[s[i + 1]])
                total -= val[s[i]];
            else
                total += val[s[i]];
        }
        return total;
    }
};