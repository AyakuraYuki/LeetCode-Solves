//
// Created by 绫仓优希 on 2024-07-05.
//

/*
5. 最长回文子串

https://leetcode.cn/problems/longest-palindromic-substring/

给你一个字符串 s，找到 s 中最长的回文子串。

示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
示例 2：
    输入：s = "cbbd"
    输出："bb"

提示：
  * 1 <= s.length <= 1000
  * s 仅由数字和英文字母组成

hint 1: How can we reuse a previously computed palindrome to compute a larger palindrome?
hint 2: If “aba” is a palindrome, is “xabax” a palindrome? Similarly is “xabay” a palindrome?
hint 3: Complexity based hint:
        If we use brute-force and check whether for every start and end position a substring is a palindrome we have
        O(n^2) start - end pairs and O(n) palindromic checks. Can we reduce the time for palindromic checks to O(1) by
        reusing some previous computation.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    // 动态规划 - 时间 O(n^2)，空间 O(n^2)
    // dp状态转移方程：P(i, j) = P(i+1, j-1) ∧ (S(i) == S(j))
    static string longestPalindrome(const string &s) {
        const unsigned int n = s.size();
        if (n < 2) return s;

        vector dp(n, vector(n, false));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }

        int max_len = 1, begin = 0;
        // 先枚举子串长度
        for (int L = 2; L <= n; ++L) {
            // 枚举左边界
            for (int i = 0; i < n; ++i) {
                // 由 L 和 i 确定右边界，即 j - i + 1 = L 可得 j
                int j = L + i - 1;
                // 如右边界越界，则可以退出循环
                if (j >= n) break;

                if (s[i] != s[j]) dp[i][j] = false;
                else {
                    if (j - i < 3) dp[i][j] = true;
                    else dp[i][j] = dp[i + 1][j - 1];
                }

                // 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，记录回文长度和起始位置
                if (dp[i][j] && j - i + 1 > max_len) {
                    max_len = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, max_len);
    }

    // --------------------------------------------------------------------------------
    // 中心扩展算法 - 时间 O(n^2)，空间 O(1)

    // 动态规划中的状态转移方程有
    // ╭ P(i, j) = true
    // ┊ P(i, i+1) = (s[i] == s[i+1])
    // ╰ P(i, j) = P(i+1, j-1) ∧ (s[i] == s[j])
    // 可以找出状态转移链：P(i, j) <- P(i+1, j-1) <- P(i+2, j-2) <- ... <- 某边界情况
    // 所以简单来说，当我们从某一个位置开始前后扩展，当遇到左右字符不同时，就可以停止扩展了，因为之后的子串都不会是回文

    static pair<int, int> expand_around_center(const string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return make_pair(left + 1, right - 1);
    }

    static string longest_palindrome_eac(const string &s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto p1 = expand_around_center(s, i, i);
            auto p2 = expand_around_center(s, i, i + 1);
            if (p1.second - p1.first > end - start) {
                start = p1.first;
                end = p1.second;
            }
            if (p2.second - p2.first > end - start) {
                start = p2.first;
                end = p2.second;
            }
        }
        return s.substr(start, end - start + 1);
    }

    // --------------------------------------------------------------------------------
    // Manacher算法

    static int expand(const string &s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return (right - left - 2) / 2;
    }

    static string longest_palindrome_manacher(string s) {
        // 为解决字符串长度奇偶问题，在原字符串每个字符之间插入占位符，来使得原字符串转变成奇数长度的字符串
        char placeholder = '.';
        string t;
        t += placeholder;
        for (const char c: s) {
            t += c;
            t += placeholder;
        }
        t += placeholder;
        s = t;

        int start = 0, end = -1, right = -1, j = -1;
        vector<int> arm_len; // 臂长
        for (int i = 0; i < s.size(); ++i) {
            int arm;
            if (right >= i) {
                int i_sym = j * 2 - i;
                int min_arm_len = min(arm_len[i_sym], right - i);
                arm = expand(s, i - min_arm_len, i + min_arm_len);
            } else {
                arm = expand(s, i, i);
            }
            arm_len.push_back(arm);
            if (i + arm > right) {
                j = i;
                right = i + arm;
            }
            if (arm * 2 + 1 > end - start) {
                start = i - arm;
                end = i + arm;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) if (s[i] != placeholder) ans += s[i];
        return ans;
    }
};

int main(int argc, char *argv[]) {
    cout << Solution::longest_palindrome_eac("cbbd") << endl;
}
