class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        const int n = nums.size();
                
        int idxMin = 0, idxMax = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > nums[idxMax]) { idxMax = i; }
            else if (nums[i] < nums[idxMin]) { idxMin = i;}
        }

        int j = min(idxMin, idxMax);
        int k = max(idxMin, idxMax);

        int front = k + 1;
        int back = nums.size() - j;
        int mixed = (j + 1) + (nums.size() - k); 

        return min({front, back, mixed});
    }
};