class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLength = 1, currentLength = 0;

        // Helper lambda to expand outward from a center
        auto expand = [&](int left, int right) {
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                currentLength = right - left + 1;
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    start = left;
                }
                left--;
                right++;
            }
        };

        for (int i = 0; i < s.size(); ++i) {
            expand(i, i);     // Odd length palindromes (e.g., "aba")
            expand(i, i + 1); // Even length palindromes (e.g., "abba")
        }

        return s.substr(start, maxLength);
    }
};