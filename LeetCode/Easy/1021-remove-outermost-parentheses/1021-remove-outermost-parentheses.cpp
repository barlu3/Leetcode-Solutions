class Solution {
public:
    string& removeOuterParentheses(string& s) {
        // (()())(())
        // ======
        // ()()()
        uint32_t n = s.size(), balance = 0, j = 0;
        for (uint32_t i = 0; i < n; i++) {
            const char c = s[i];
            balance += (c == '(') ? 1 : -1;
            if ((balance == 1 && c=='(') || (balance==0 && c==')')) continue;
            s[j++] = s[i];
        }
        s.resize(j);
        return s;
    }
};