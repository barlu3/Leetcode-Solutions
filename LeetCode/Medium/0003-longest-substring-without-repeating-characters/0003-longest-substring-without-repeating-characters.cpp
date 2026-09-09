class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> mp;
        int left = 0, best = 0, n = s.size();
        for (int right = 0; right < n; right++) {
            while (mp.count(s[right])) {
                mp.erase(s[left]);
                left++;
            }
            mp.insert(s[right]);
            best = max(best, right - left + 1);
        }
        return best;
    }
};