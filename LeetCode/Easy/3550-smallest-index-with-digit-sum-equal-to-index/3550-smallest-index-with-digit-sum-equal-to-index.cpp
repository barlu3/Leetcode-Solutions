class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        if (nums.empty()) return -1;

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int cand = 0, number = nums[i];
            while (number > 0) {
                cand += number % 10;
                number /= 10;
            }
            if (cand == i) return i;
        }
        return -1;
    }
};