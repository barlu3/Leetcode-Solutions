class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> mp;
        size_t left = 0, best = 0;
        for (size_t right = 0; right < s.size(); right++) {
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