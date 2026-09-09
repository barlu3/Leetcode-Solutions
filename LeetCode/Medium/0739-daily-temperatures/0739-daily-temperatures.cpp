class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        size_t n = temperatures.size(), prevIndex;
        vector<int> ans(n, 0);
        stack<int> stck;

        for (int i = 0; i < n; i++) {
            while (!stck.empty() && temperatures[i] > temperatures[stck.top()]) {
                prevIndex = stck.top();
                stck.pop();
                ans[prevIndex] = i - prevIndex;
            }
            stck.push(i);
        }
        return ans;
    }
};