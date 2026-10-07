class Solution {
    vector<string> ans;
    void dfs(int start, int last, char open, char close, string s ) {
        int balance = 0;
        for (int i = start; i < s.size(); i++) {
            if (s[i] == open) balance++;
            if (s[i] == close) balance--;

            if (balance >= 0) continue;

            for (int j = last; j<= i; j++) {
                if (s[j] == close && (j == last || s[j-1] != close)) {
                    dfs(i, j, open, close, s.substr(0,j) + s.substr(j+1) );
                }
            } 
            return;
        }
        reverse(s.begin(), s.end());

        if (open == '(') {
            dfs(0, 0, ')', '(', s);
        }
        else {
            ans.push_back(s);
        }
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        dfs(0, 0, '(', ')', s);
        return ans;
    }
};