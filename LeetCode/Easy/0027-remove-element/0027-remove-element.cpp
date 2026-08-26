class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //analyze the vector to find instances of val
        //using for loop for each index
        //then for each instances of val, remove from list
        //and return amount of instances of vector
        //left in the array 
        if (nums.size() == 0) {
            return 0;
        }
        for (auto it = nums.begin(); it != nums.end() + 1; ++it) {

            it = find(nums.begin(), nums.end(), val);

                if (it != nums.end()) {
                    nums.erase(it);
                
                } 
        }
    
    return nums.size();
    }
};