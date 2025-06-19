//
// Created by 绫仓优希 on 25-6-19.
//

/*
32. 最长有效括号

https://leetcode.cn/problems/longest-valid-parentheses/

给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。

示例 1：
    输入：s = "(()"
    输出：2
    解释：最长有效括号子串是 "()"
示例 2：
    输入：s = ")()())"
    输出：4
    解释：最长有效括号子串是 "()()"
示例 3：
    输入：s = ""
    输出：0

提示：
  * 0 <= s.length <= 3 * 104
  * s[i] 为 '(' 或 ')'
 */

#include <stack>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    static int longestValidParentheses(const string& s) {
        int left = 0, right = 0, max_ans = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') left++;
            else right++;
            if (left == right) max_ans = max(max_ans, 2 * right);
            else if (right > left) left = right = 0;
        }

        left = right = 0; // reset
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '(') left++;
            else right++;
            if (left == right) max_ans = max(max_ans, 2 * left);
            else if (left > right) left = right = 0;
        }

        return max_ans;
    }
};

class DPSolution {
public:
    static int longestValidParentheses(const string& s) {
        int max_ans = 0;
        const int n = s.size();
        vector dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2; // + 2（增量）
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2; // 前序结果 + 当前结果 + 2（增量）
                }
                max_ans = max(max_ans, dp[i]);
            }
        }
        return max_ans;
    }
};

class StackSolution {
public:
    static int longestValidParentheses(const string& s) {
        int max_ans = 0;
        stack<int> stack;
        stack.push(-1);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stack.push(i); // 入一个左括号
            } else {
                stack.pop();
                if (stack.empty()) {
                    stack.push(i); // 空栈时入一个右括号
                } else {
                    max_ans = max(max_ans, i - stack.top()); // 计算当前最长连续有效括号组
                }
            }
        }
        return max_ans;
    }
};
