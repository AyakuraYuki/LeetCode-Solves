//
// Created by 绫仓优希 on 2024-09-03.
//

/*
6. Z 字形变换

https://leetcode.cn/problems/zigzag-conversion/

将一个给定字符串 s 根据给定的行数 numRows，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

P   A   H   N
A P L S I I G
Y   I   R

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
请你实现这个将字符串进行指定行数变换的函数：
string convert(string s, int numRows);

示例 1：
    输入：s = "PAYPALISHIRING", numRows = 3
    输出："PAHNAPLSIIGYIR"
示例 2：
    输入：s = "PAYPALISHIRING", numRows = 4
    输出："PINALSIGYAHRPI"
    解释：
        P     I    N
        A   L S  I G
        Y A   H R
        P     I
示例 3：
    输入：s = "A", numRows = 1
    输出："A"

提示：
  * 1 <= s.length <= 1000
  * s 由英文字母（小写和大写）、',' 和 '.' 组成
  * 1 <= numRows <= 1000
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    static string convert(const string &s, const int numRows) {
        if (numRows < 2) { return s; }
        vector<string> row(numRows);
        int i = 0, flag = -1;
        for (const char c: s) {
            row[i].push_back(c);
            // Z字抖动
            if (i == 0 || i == numRows - 1) flag = -flag;
            i += flag;
        }
        string ans;
        for (const string &r: row) ans += r;
        return ans;
    }

    static string direct_convert(const string &s, const int numRows) {
        const unsigned int n = s.size();
        const int r = numRows;
        if (r == 1 || r >= n) return s;

        // Z字变换周期公式：t = 2r - 2
        // t 是一个周期的步数，r 是行的数量，2r 表示一个来回，返回方向不需要填充顶行和末行所以需要减去 2
        const int t = r * 2 - 2;

        /*
         * 下面以一个需要转换成 4 行Z字型矩阵的模式，画表总结规律
         *
         * 0+0t          0+1t           0+2t           0+3t           ...
         * 1+0t     1t-1 1+1t      2t-1 1+2t      3t-1 1+3t      4t-1 ...
         * 2+0t 1t-2     2+1t 2t-2      2+2t 3t-2      2+3t 4t-2      ...
         * 3+0t          3+1t           3+2t           3+3t           ...
         *
         * 这个模式下一个周期 t = 2r - 2 = 6，代换出结果有
         * 0     6       12       18       ...
         * 1   5 7    11 13    17 19    23 ...
         * 2 4   8 10    14 16    20 22    ...
         * 3     9       15       21       ...
         * 代换后这里面的数字就是原字符串的字符index编号
         */

        string ans;
        // 枚举矩阵的行
        for (int i = 0; i < r; ++i) {
            // 枚举每个周期的起始下标
            for (int j = 0; j + i < n; j += t) {
                ans += s[j + i]; // 当前周期第一个字符
                if (0 < i && i < r - 1 && j + t - i < n) {
                    ans += s[j + t - i]; // 当前周期第二个字符
                }
            }
        }
        return ans;
    }
};
