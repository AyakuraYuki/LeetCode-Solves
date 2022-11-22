#include <iostream>

using std::string;

class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

int main() {
    Solution solution = Solution();
    std::cout << solution.isAnagram("anagram", "nagaram") << std::endl; // true
    std::cout << solution.isAnagram("rat", "car") << std::endl; // false
}
