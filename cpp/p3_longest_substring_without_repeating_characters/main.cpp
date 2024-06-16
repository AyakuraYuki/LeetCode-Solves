//
// Created by 绫仓优希 on 2024-06-16.
//

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        const size_t n = s.size();
        if (n <= 1) {
            // 对只有一个字符或者空字符的 s 断路
            return static_cast<int>(n);
        }
        unordered_map<char, int> mp; // 记录字符最后出现的位置
        int ans = 0; // 最长不重复子串的长度
        int left = 0; // 左边界
        int right; // 滑动右边界
        for (right = 0; right < n; ++right) {
            if (mp.contains(s[right])) {
                ans = max(ans, right - left);
                left = max(left, mp[s[right]] + 1);
            }
            mp[s[right]] = right;
        }
        return max(ans, right - left);
    }
};

int main(int argc, char *argv[]) {
    cout << (new Solution())->lengthOfLongestSubstring("abcabcbb") << endl;
}
