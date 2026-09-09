class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int minDist = INT_MAX, n = nums.size();
        for (int i = 0; i < n; i++){
            if (nums[i] == target) {
                minDist = std::min(minDist, std::abs(i - start));
            }
        }
        return minDist;
    }
};