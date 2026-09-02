class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = nums1.size();
        if (n == 1) return true;        //base case 1, nums1 is single element

        int odd = 0, even = 0;
        for (int x : nums1) (x & 1) ? ++odd : ++even;
        if (n == odd || n == even) return true;     //base case 2, nums1 is all even or odd

        auto canForce = [&](int parityT) -> bool {
            //need to keep track of only one or two odd numbers
            for (auto num : nums1) {
                int needFlipEven = (parityT == 1) ? even : 0;
                int needFlipOdd = (parityT == 0) ? odd : 0;
                if (needFlipEven > 0 && odd < 1) return false;
                if (needFlipOdd > 0 && odd < 2) return false;
            }
            return true;
        };

        return canForce(0) || canForce(1);
    }
};