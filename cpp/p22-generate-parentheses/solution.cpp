//
// Created by 绫仓优希 on 2024-09-11.
//

/*
22. 括号生成

https://leetcode.cn/problems/generate-parentheses/

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
    输入：n = 3
    输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：
    输入：n = 1
    输出：["()"]

提示：
  * 1 <= n <= 8
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    static vector<string> generateParenthesis(const int n) {
        vector<string> ans;
        back_tracking(ans, n, "", 0, 0);
        return ans;
    }

private:
    static void back_tracking(vector<string> &ans, const int n, string s, const int open, const int close) {
        if (s.size() == n * 2) {
            // 有多少组括号，就应该有 2 倍于括号组数的字符个数，这时就应该写入 ans 了
            ans.push_back(s);
            return;
        }
        if (open < n) {
            // 这个条件是，填充 ( 直到应该出现 n 组括号为止
            s.push_back('(');
            back_tracking(ans, n, s, open + 1, close);
            s.pop_back();
        }
        if (close < open) {
            // 这个条件做的事情是，遇到单独的 ( 时，就立刻在后面补上 )，使得括号匹配
            s.push_back(')');
            back_tracking(ans, n, s, open, close + 1);
            s.pop_back();
        }
    }
};
