class Solution {
public:
    int reverseDegree(string s) {
        int ans = 0, k = 1;
        for (char c : s) {
            ans += (123 - static_cast<int>(c)) * k;
            k++;
        }
        return ans;
    }
};