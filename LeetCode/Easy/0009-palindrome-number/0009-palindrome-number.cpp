class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }

        string temp = to_string(x);
        reverse(temp.begin(), temp.end());
        string temp2 = to_string(x);

        if (temp2 == temp) {
            return true;
        }

        return false;
    }
};