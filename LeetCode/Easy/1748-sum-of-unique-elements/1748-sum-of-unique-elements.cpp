class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int Uarray[101] = {0};
        int sum = 0;
        int size = nums.size();
        for (int i = 0; i < size; ++i) {
            Uarray[nums.at(i)]++;
        }
        for (int i = 0; i < size; ++i) {
            if (Uarray[nums.at(i)] == 1) sum += nums.at(i);
        }
        return sum;
    }
};