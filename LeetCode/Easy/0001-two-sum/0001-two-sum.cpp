class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       unordered_map<int, int> hashMap;
       int n = nums.size();
        for (auto i = 0; i < n; i++) {
            int comp = target - nums[i];
            if (hashMap.count(comp)) {
                return {hashMap[comp], i};
            }
            hashMap[nums[i]] = i;
        }

        return {};
    }
};