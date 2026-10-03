#include <string>
using namespace std;

class Solution {
    // Index of the next valid character at or before i, or -1 if none
    int nextValid(const string& str, int i) {
        int skip = 0;
        while (i >= 0) {
            if (str[i] == '#') {
                skip++;
                i--;
            } else if (skip > 0) {
                skip--;
                i--;
            } else {
                break;
            }
        }
        return i;
    }

public:
    bool backspaceCompare(string s, string t) {
        int i = (int)s.size() - 1, j = (int)t.size() - 1;
        while (true) {
            i = nextValid(s, i);
            j = nextValid(t, j);
            if (i < 0 && j < 0) return true;   // both exhausted
            if (i < 0 || j < 0) return false;  // one ended first
            if (s[i] != t[j]) return false;
            i--;
            j--;
        }
    }
};