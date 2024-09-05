//
// Created by 绫仓优希 on 2024-09-05.
//

/*
7. 整数反转

https://leetcode.cn/problems/reverse-integer/

给你一个 32 位的有符号整数 x，返回将 x 中的数字部分反转后的结果。
如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1]，就返回 0。
假设环境不允许存储 64 位整数（有符号或无符号）。

示例 1：
    输入：x = 123
    输出：321
示例 2：
    输入：x = -123
    输出：-321
示例 3：
    输入：x = 120
    输出：21
示例 4：
    输入：x = 0
    输出：0

提示：
  * -2^31 <= x <= 2^31 - 1
 */

#include <climits>

class Solution {
public:
    // 再次提醒：不能用 64 位整数，言下之意是不能用 long 或者 long long
    static int reverse(const int x) {
        int res = 0, in = x, temp = 0;
        constexpr int lower = INT_MIN / 10, upper = INT_MAX / 10;
        while (in != 0) {
            temp = in % 10;
            if (res > upper || (res == upper && temp > 7)) return 0;
            if (res < lower || (res == lower && temp < -8)) return 0;
            res = res * 10 + temp;
            in /= 10;
        }
        return res;
    }
};
