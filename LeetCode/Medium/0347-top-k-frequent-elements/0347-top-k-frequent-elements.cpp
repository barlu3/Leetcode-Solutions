class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> holder;
        unordered_map<int, int> freq;

        for (auto i : nums) freq[i]++;

        for (auto& p : freq) {
            holder.push({p.second, p.first});
        }

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            ans.push_back(holder.top().second);
            holder.pop();
        }

        return ans;
    }
};