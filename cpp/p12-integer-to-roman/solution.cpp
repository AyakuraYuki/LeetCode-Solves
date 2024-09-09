//
// Created by 绫仓优希 on 2024-09-09.
//

/*
12. 整数转罗马数字

https://leetcode.cn/problems/integer-to-roman/

七个不同的符号代表罗马数字，其值如下：

（符号 - 值）
I - 1
V - 5
X - 10
L - 50
C - 100
D - 500
M - 1000

罗马数字是通过添加从最高到最低的小数位值的转换而形成的。将小数位值转换为罗马数字有以下规则：
  * 如果该值不是以 4 或 9 开头，请选择可以从输入中减去的最大值的符号，将该符号附加到结果，减去其值，然后将其余部分转换为罗马数字。
  * 如果该值以 4 或 9 开头，使用 减法形式，表示从以下符号中减去一个符号，例如 4 是 5 (V) 减 1 (I): IV ，9 是 10 (X) 减 1 (I)：IX。
    仅使用以下减法形式：4 (IV)，9 (IX)，40 (XL)，90 (XC)，400 (CD) 和 900 (CM)。
  * 只有 10 的次方（I, X, C, M）最多可以连续附加 3 次以代表 10 的倍数。你不能多次附加 5 (V)，50 (L) 或 500 (D)。
    如果需要将符号附加4次，请使用 减法形式。

给定一个整数，将其转换为罗马数字。

示例 1：
    输入：num = 3749
    输出："MMMDCCXLIX"
    解释：
        3000 = MMM 由于 1000 (M) + 1000 (M) + 1000 (M)
        700 = DCC 由于 500 (D) + 100 (C) + 100 (C)
        40 = XL 由于 50 (L) - 10 (X)
        9 = IX 由于 10 (X) - 1 (I)
        注意：49 不是 50 (L) - 1 (I) 因为转换是基于小数位的
示例 2：
    输入：num = 58
    输出："LVIII"
    解释：
        50 = L
         8 = VIII
示例 3：
    输入：num = 1994
    输出："MCMXCIV"
    解释：
        1000 = M
         900 = CM
          90 = XC
           4 = IV

提示：
  * 1 <= num <= 3999
*/

#include <string>
using namespace std;

// 转换法：利用符号转换表定义，扫表转换字符
//
// 数值 - 符号 转换表，并且填充特殊规则：
//   - I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
//   - X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
//   - C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
const pair<int, string> roman_symbols[] = {
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"},
};

// 硬编码：根据已知码表，对数值取模转换
// 码表按顺序分别是每个数字在这一位上的表示形式，其中 0 对应的位都是空字符串
// 每个数字：0, 1, 2, 3, 4, 5, 6, 7, 8, 9
// 对于【千】位，应题干数值范围，千位最大是 3，所以只给出了 0, 1, 2, 3 的固定码
const string thousands[] = {"", "M", "MM", "MMM"};
const string hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const string tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const string ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

class Solution {
public:
    // 转换法 - 说白了就是优化了 if...else... 法
    static string intToRoman(int num) {
        string roman;
        for (const auto &[value, symbol]: roman_symbols) {
            while (num >= value) {
                roman += symbol;
                num -= value;
            }
            if (num == 0) break;
        }
        return roman;
    }

    // 硬编码
    static string int_to_roman_codec_table(int num) {
        return thousands[num / 1000] + hundreds[num % 1000 / 100] + tens[num % 100 / 10] + ones[num % 10];
    }
};
