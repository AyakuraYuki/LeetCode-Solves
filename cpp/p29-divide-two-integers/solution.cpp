//
// Created by 绫仓优希 on 2024-09-26.
//

/*
29. 两数相除

https://leetcode.cn/problems/divide-two-integers/

给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用 乘法、除法和取余运算。
整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8，-2.7335 将被截断至 -2。
返回被除数 dividend 除以除数 divisor 得到的商。
注意：假设我们的环境只能存储 32位 有符号整数，其数值范围是 [−2^31, 2^31 − 1]。本题中，如果商严格大于 2^31 − 1，则返回 2^31 − 1；如果商严格小于 -2^31，则返回 -2^31。

示例 1:
    输入: dividend = 10, divisor = 3
    输出: 3
    解释: 10/3 = 3.33333.. ，向零截断后得到 3 。
示例 2:
    输入: dividend = 7, divisor = -3
    输出: -2
    解释: 7/-3 = -2.33333.. ，向零截断后得到 -2 。

提示：
  * -231 <= dividend, divisor <= 231 - 1
  * divisor != 0
 */

#include <climits>

class Solution {
public:
    static int divide(const int dividend, const int divisor) {
        if (dividend == 0) return 0;
        if (divisor == 1) return dividend;
        // 除数是 -1，被除数如果不是最小 int 就返回它的相反数；否则直接返回最大整数。这里的「否则」即被除数是 INT_MIN 已经是最小 int 了。
        if (divisor == -1) return dividend > INT_MIN ? -dividend : INT_MAX;

        int a = dividend;
        int b = divisor;

        // 检查是否包含相异符号
        bool sign = true;
        if ((a > 0 && b < 0) || (a < 0 && b > 0)) sign = false;
        // 从负数翻转到正数会有越界问题，但反过来则不会，所以这里只翻转正数
        a = a > 0 ? -a : a;
        b = b > 0 ? -b : b;

        const int ans = div(a, b);
        if (sign)
            return ans > INT_MAX ? INT_MAX : ans;
        return -ans;
    }

    static int div(const int a, const int b) {
        if (a > b) return 0;
        int count = 1, sum = b;
        while (sum >= a - sum) {
            count += count; // 最小解翻倍
            sum += sum; // 累积值翻倍
        }
        return count + div(a - sum, b);
    }
};
