//
// Created by 绫仓优希 on 2024-07-01.
//

/*
13. 罗马数字转整数

https://leetcode.cn/problems/roman-to-integer/

罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

例如，罗马数字 2 写做 II，即为两个并列的 1。12 写做 XII，即为 X + II。27 写做 XXVII，即为 XX + V + II。

通常情况下，罗马数字中小的数字在大的数字的右边。
但也存在特例，例如 4 不写做 IIII，而是 IV。
数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

  - I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
  - X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。
  - C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。

示例 1:
    输入: s = "III"
    输出: 3
示例 2:
    输入: s = "IV"
    输出: 4
示例 3:
    输入: s = "IX"
    输出: 9
示例 4:
    输入: s = "LVIII"
    输出: 58
    解释: L = 50, V= 5, III = 3.
示例 5:
    输入: s = "MCMXCIV"
    输出: 1994
    解释: M = 1000, CM = 900, XC = 90, IV = 4.

提示：
  - 1 <= s.length <= 15
  - s 仅含字符 ('I', 'V', 'X', 'L', 'C', 'D', 'M')
  - 题目数据保证 s 是一个有效的罗马数字，且表示整数在范围 [1, 3999] 内
  - 题目所给测试用例皆符合罗马数字书写规则，不会出现跨位等情况。
  - IL 和 IM 这样的例子并不符合题目要求，49 应该写作 XLIX，999 应该写作 CMXCIX 。
  - 关于罗马数字的详尽书写规则，可以参考 罗马数字 - Mathematics 。

hint 1: Problem is simpler to solve by working the string from back to front and using a map.
 */

#include <string>
using namespace std;

class Solution {
public:
    static int romanToInt(const string &s) {
        int sum = 0, head = get_value(s[0]);
        for (int i = 1; i < s.length(); ++i) {
            const int num = get_value(s[i]);
            if (head < num) { sum -= head; } else { sum += head; }
            head = num;
        }
        sum += head;
        return sum;
    }

private:
    static int get_value(const char ch) {
        switch (ch) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }
};

class ExtendSolution {
public:
    static int roman_to_int(const string &s) {
        string roman = s;
        replace_all(roman, "IV", "a");
        replace_all(roman, "IX", "b");
        replace_all(roman, "XL", "c");
        replace_all(roman, "XC", "d");
        replace_all(roman, "CD", "e");
        replace_all(roman, "CM", "f");

        int result = 0;
        for (int i = 0; i < roman.length(); ++i) {
            result += get_value(roman[i]);
        }
        return result;
    }

private:
    // 扩展字符：根据特殊规则，定义额外的 a, b, c, d, e, f 字符，用于转换成特殊规则的数值
    // 为了使用特殊规则，需要替换原字符串中的特殊规则字符
    static int get_value(const char ch) {
        switch (ch) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            // extend chars
            case 'a': return 4;
            case 'b': return 9;
            case 'c': return 40;
            case 'd': return 90;
            case 'e': return 400;
            case 'f': return 900;
            default: return 0;
        }
    }

    static bool replace(string &s, const string &from, const string &to) {
        const size_t pos = s.find(from);
        if (pos == string::npos) return false;
        s.replace(pos, from.length(), to);
        return true;
    }

    static void replace_all(string &s, const string &from, const string &to) {
        if (from.empty()) return;
        size_t pos = 0;
        while ((pos = s.find(from, pos)) != string::npos) {
            s.replace(pos, from.length(), to);
            pos += to.length();
        }
    }
};
