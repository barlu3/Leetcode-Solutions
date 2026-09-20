class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0, k = 1;
        for (char c : s) {
            ans += (26 - (c - 'a')) * k;
            k++;
        }
        return ans;
    }
};