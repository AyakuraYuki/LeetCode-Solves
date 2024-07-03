//
// Created by 绫仓优希 on 2024-06-16.
//

/*
3. 无重复字符的最长子串

https://leetcode.cn/problems/longest-substring-without-repeating-characters/

给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。

示例 1:
    输入: s = "abcabcbb"
    输出: 3
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
    输入: s = "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
    输入: s = "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
        请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


提示：
  - 0 <= s.length <= 5 * 104
  - s 由英文字母、数字、符号和空格组成
 */

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
