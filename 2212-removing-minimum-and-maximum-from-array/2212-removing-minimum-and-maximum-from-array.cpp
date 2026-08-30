class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int idxMin = 0, idxMax = 0;
        
        int minimum = nums[0];
        int maximum = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > maximum) { maximum = nums[i]; idxMax = i;}
            else if (nums[i] < minimum) { minimum = nums[i]; idxMin = i;}
        }

        int j = min(idxMin, idxMax);
        int k = max(idxMin, idxMax);

        int front = k + 1;
        int back = nums.size() - j;
        int mixed = (j + 1) + (nums.size() - k); 

        return min({front, back, mixed});
    }
};