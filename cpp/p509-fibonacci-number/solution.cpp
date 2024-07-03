//
// Created by 绫仓优希 on 2024-07-02.
//

/*
509. 斐波那契数
（经典动态规划）

https://leetcode.cn/problems/fibonacci-number/

斐波那契数（通常用 F(n) 表示）形成的序列称为斐波那契数列。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

    F(0) = 0，F(1) = 1
    F(n) = F(n - 1) + F(n - 2)，其中 n > 1

给定 n，请计算 F(n)。

示例 1：
    输入：n = 2
    输出：1
    解释：F(2) = F(1) + F(0) = 1 + 0 = 1
示例 2：
    输入：n = 3
    输出：2
    解释：F(3) = F(2) + F(1) = 1 + 1 = 2
示例 3：
    输入：n = 4
    输出：3
    解释：F(4) = F(3) + F(2) = 2 + 1 = 3

提示：
  - 0 <= n <= 30
 */

#include <vector>
using namespace std;

class Solution {
public:
    static int fib(const int n) {
        if (n <= 1) return n; // F(0) = 0，F(1) = 1
        vector dp(n + 1, 0);
        dp[0] = 0, dp[1] = 1; // F(0) = 0，F(1) = 1
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 2] + dp[i - 1]; // F(n) = F(n-1) + F(n-2)
        }
        return dp[n];
    }
};