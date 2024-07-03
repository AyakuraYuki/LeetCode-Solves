//
// Created by 绫仓优希 on 2024-07-02.
//

/*
20. 有效的括号

https://leetcode.cn/problems/valid-parentheses/

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
有效字符串需满足：
1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。
3. 每个右括号都有一个对应的相同类型的左括号。

示例 1：
    输入：s = "()"
    输出：true
示例 2：
    输入：s = "()[]{}"
    输出：true
示例 3：
    输入：s = "(]"
    输出：false

提示：
  - 1 <= s.length <= 104
  - s 仅由括号 '()[]{}' 组成

hint 1: Use a stack of characters.
hint 2: When you encounter an opening bracket, push it to the top of the stack.
hint 3: When you encounter a closing bracket, check if the top of the stack was the opening for it.
        If yes, pop it from the stack. Otherwise, return false.
 */

#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 用 switch...case... 来匹配
// 缺点：有重复代码，不够意思
class Solution {
public:
    static bool isValid(const string &s) {
        const size_t n = s.size();
        if (n % 2 != 0) return false; // 有效的括号不能是奇数长度

        stack<char> left_stack;
        for (int i = 0; i < n; ++i) {
            switch (const char ch = s[i]) {
                case '(':
                case '[':
                case '{': {
                    left_stack.push(ch);
                    break;
                }
                case ')': {
                    if (left_stack.empty() || left_stack.top() != '(') return false;
                    left_stack.pop();
                    break;
                }
                case ']': {
                    if (left_stack.empty() || left_stack.top() != '[') return false;
                    left_stack.pop();
                    break;
                }
                case '}': {
                    if (left_stack.empty() || left_stack.top() != '{') return false;
                    left_stack.pop();
                    break;
                }
                default: return false; // 不合法的字符
            }
        }

        return left_stack.empty();
    }
};

// 用 map 声明括号组来匹配
class MapSolution {
public:
    static bool isValid(const string &s) {
        if (s.size() % 2 != 0) return false; // 有效的括号不能是奇数长度

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        stack<char> left_stack;
        for (char ch: s) {
            if (pairs.contains(ch)) {
                // 右括号，去匹配栈顶元素
                if (left_stack.empty() || left_stack.top() != pairs[ch]) {
                    return false;
                }
                left_stack.pop();
            } else {
                // 左括号
                left_stack.push(ch);
            }
        }

        return left_stack.empty();
    }
};

// 动态规划解决括号匹配
class DpSolution {
public:
    static bool isValid(const string &s) {
        const size_t n = s.size();
        if (n % 2 != 0) return false; // 有效的括号不能是奇数长度

        vector dp(n + 1, 0);
        auto matched = [](const char &a, const char &b) {
            return (a == '(' && b == ')') || (a == '[' && b == ']') || (a == '{' && b == '}');
        };

        for (int i = 2; i <= n; ++i) {
            char previous = s[i - 2], current = s[i - 1];
            if (current == '(' || current == '[' || current == '{') {
                continue; // 左括号则跳到下一组使得 current 变为 previous
            }
            if (matched(previous, current)) {
                dp[i] = dp[i - 2] + 2; // 一组括号
            } else if (const int dis = i - dp[i - 1]; dis > 1 && matched(s[dis - 2], current)) {
                dp[i] = dp[i - 1] + 2 + dp[dis - 2]; // 一组括号并且前序在比较靠前的位置
            } else {
                return false; // 非法字符
            }
        }

        return dp[n] == n;
    }
};
