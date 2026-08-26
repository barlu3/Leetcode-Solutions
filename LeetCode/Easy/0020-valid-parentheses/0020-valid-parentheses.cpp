class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false;
        vector<char> stack; 
        for (auto c : s) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push_back(c);
            }
            else if (!stack.empty() && c == ')' && stack.back() == '(') stack.pop_back();
            else if (!stack.empty() && c == ']' && stack.back() == '[') stack.pop_back();
            else if (!stack.empty() && c == '}' && stack.back() =='{') stack.pop_back();
            else return false;
        }
        if (stack.size() == 0) return true;

        return false;
    }
};