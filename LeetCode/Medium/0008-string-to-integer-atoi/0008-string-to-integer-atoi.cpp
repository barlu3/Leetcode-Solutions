#include <cctype>
#include <string>

class Solution {
public:
    int myAtoi(string s) {
        //check whitespace
        //check signs
        //store each integer in the string into a char
            //if index[] is 0 - '0' ignore
            //if s has no digits return 0
        //use while loop to round into range
    
    long long ans = 0;
    int counter = 0;
    int sign = 1;

    //ignore leading whitespace
    while (counter < s.size() && s.at(counter) == ' ') {
        counter++;
    }

    //sign check
    if (counter < s.size() && (s.at(counter) == '+' || s.at(counter) == '-')) {
        sign = (s.at(counter++) == '-') ? -1 : 1;
    }
    cout << sign;

    //to digit loop
    while (counter < s.size() && isdigit(s.at(counter))) {
        int temp = s.at(counter) - '0';
        if (ans > INT_MAX / 10 || (ans == INT_MAX / 10 && temp > INT_MAX % 10)) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }
        ans = ans * 10 + temp;
        counter++;
    }
    
    return ans * sign;
    }
};