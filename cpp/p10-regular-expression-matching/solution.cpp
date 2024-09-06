//
// Created by 绫仓优希 on 2024-09-06.
//

/*
10. 正则表达式匹配

https://leetcode.cn/problems/regular-expression-matching/

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
* '.' 匹配任意单个字符
* '*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s 的，而不是部分字符串。

示例 1：
    输入：s = "aa", p = "a"
    输出：false
    解释："a" 无法匹配 "aa" 整个字符串。
示例 2:
    输入：s = "aa", p = "a*"
    输出：true
    解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3：
    输入：s = "ab", p = ".*"
    输出：true
    解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

提示：
  * 1 <= s.length <= 20
  * 1 <= p.length <= 20
  * s 只包含从 a-z 的小写字母。
  * p 只包含从 a-z 的小写字母，以及字符 . 和 *。
  * 保证每次出现字符 * 时，前面都匹配到有效的字符
 */

#include <string>
using namespace std;

class Solution {
public:
    static bool isMatch(const string &s, const string &p) {
        return dfs(s, p, s.size() - 1, p.size() - 1);
    }

    static bool dfs(const string &s, const string &p, int i, int j) {
        if (j < 0) return i < 0;
        if (i < 0) return p[j] == '*' && dfs(s, p, i, j - 2);
        return ((s[i] == p[j] || p[j] == '.') && dfs(s, p, i - 1, j - 1))
               || (p[j] == '*' && (
                       (s[i] == p[j - 1] || p[j - 1] == '.')
                       && (dfs(s, p, i - 1, j - 2) || dfs(s, p, i - 1, j) || dfs(s, p, i, j - 2))
                       || dfs(s, p, i, j - 2)
                   ));
    }
};
