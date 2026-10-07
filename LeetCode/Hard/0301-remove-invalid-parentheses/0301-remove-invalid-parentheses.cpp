class Solution {
    bool isValid(const string& t) {
        int bal = 0;
        for (char c : t) {
            if (c == '(') bal++;
            else if (c == ')' && --bal < 0) return false;
        }
        return bal == 0;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> seen{s};
        queue<string> q;
        q.push(s);

        while (!q.empty() && res.empty()) {
            int levelsize = q.size();
            for (int i = 0 ; i < levelsize; i++) {
                string cur = q.front(); q.pop();

                if (isValid(cur)) {
                    res.push_back(cur); continue;
                }

                if (!res.empty()) continue;

                for (int j = 0; j < (int)cur.size(); ++j) {
                    if (cur[j] != '(' && cur[j] != ')') continue;
                    if (j > 0 && cur[j] == cur[j-1]) continue;
                    string next = cur.substr(0,j) + cur.substr(j + 1);
                    if (seen.insert(next).second) q.push(next);
                 }
            }
        }
        return res;
    }
};