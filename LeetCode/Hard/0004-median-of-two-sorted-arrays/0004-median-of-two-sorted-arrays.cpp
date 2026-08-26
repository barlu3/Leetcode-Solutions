class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //make a vector data array with size of both vectors
        //merge vectors into new vector
        //sort by least to greatest
        //find median ???
        //if size of merged vector is odd, median is index at midpoint
        //if size of merged vector is even, median is sum of two indexes
        //at middle divided by 2
        
        double median;

        vector<int> nums12(nums1.size() + nums2.size());
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), 
            nums12.begin());
        sort(nums12.begin(), nums12.end());

        if (nums12.size() % 2 != 0) {
            median = nums12[nums12.size() / 2];
        } 
        else {
            double fnum = ((nums12.size() / 2.0) + 0.5);
            double snum = ((nums12.size() / 2.0) - 0.5);
            median = (nums12[fnum] + nums12[snum]) / 2.0;
        
        }
        return median;
    }  
};