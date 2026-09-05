class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (auto& word : strs) {
            int count[26]={0};
            for (char c : word) {
                count[c - 'a']++;
            }

            string key;
            for (auto i = 0; i < 26; i++) {
                key += "#";
                key += to_string(count[i]);
            }

            groups[key].push_back(word);
        }

        vector<vector<string>> results;

        for (auto& keys : groups) {
            results.push_back(keys.second);
        }
        return results;
    }
};