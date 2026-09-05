class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, int> hashMap;
        for (int i = 0; i<nums.size(); i++) {
            if (hashMap.count(nums[i])) {
                return true;
            }
            hashMap[nums[i]];
        }
        return false;
    }
};