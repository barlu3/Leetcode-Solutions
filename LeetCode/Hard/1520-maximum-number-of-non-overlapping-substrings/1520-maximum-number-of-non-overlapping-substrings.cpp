class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();
        vector<int> first(26,n);
        vector<int> last(26, -1);

        //find the first and last occurences of each character in the string
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        for (int c = 0; c < 26; c++) {
            if(last[c] == -1) continue; //not in string

            //initialize the window for each character in the string
            int l = first[c];
            int r = last[c];
            bool valid = true;
            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';
                if (first[x] < l) {  //if we see a character that appears in the substring and 
                                    //its first occurence is before our left pointer, the substring is false and our starting point is wrong
                    valid = false;
                    break;
                }
                r = max(r, last[x]);    //if we come across a valid character, set the right window
                                        //to last occurence of r
            }
            if (valid) intervals.push_back({r, l}); // if valid push back the pair of indices from the window
        }

        sort(intervals.begin(), intervals.end());   // sort by earliest ending 

        vector<string> ans;

        int prevEnd = -1;
        for(auto [r,l] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));  // push back non overalpping intervals
                prevEnd = r;
            }
        }

        return ans;
    }
};