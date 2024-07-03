//
// Created by 绫仓优希 on 2024-07-02.
//

/*
70. 爬楼梯

https://leetcode.cn/problems/climbing-stairs/

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

示例 1：
    输入：n = 2
    输出：2
    解释：有两种方法可以爬到楼顶。
        1. 1 阶 + 1 阶
        2. 2 阶
示例 2：
    输入：n = 3
    输出：3
    解释：有三种方法可以爬到楼顶。
        1. 1 阶 + 1 阶 + 1 阶
        2. 1 阶 + 2 阶
        3. 2 阶 + 1 阶

提示：
  - 1 <= n <= 45

hint 1: To reach nth step, what could have been your previous steps? (Think about the step sizes)
 */

#include <vector>
using namespace std;

// 优化空间的动态规划
// time: 0 ms (100%); rem: 6.96 MB (80.98%)
class Solution {
public:
    static int climbStairs(const int n) {
        if (n <= 2) return n;
        // 因为推导公式使用的参数最多用到了最后3个参数，所以不需要使用数组保存记录，只需要处理好末尾3个参数的结果
        // 因此我们可以简化参数，使用 p、q、r 代表公式 F(n) = F(n-1) + F(n-2)，则有：
        // p: F(n-2), q: F(n-1), r: F(n)
        int p = 1, q = 1, r = 2;
        for (int i = 2; i < n; ++i) {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};

// ----------------------------------------------------------------------------------------------------

// 动态规划的标准解法
// time: 0 ms (100%); rem: 7.22 MB (29.32%)
class DpSolution {
public:
    static int climbStairs(const int n) {
        if (n <= 2) return n;
        vector dp(n + 1, 0);
        // F(0) 表示从第 0 阶走到第 0 阶，只有 1 种方案
        // F(1) 表示从第 0 阶走到第 1 阶，也是只有 1 种方案
        // F(2) 表示从第 0 阶走到第 2 阶，可以走 1+1，也可以走 2，所以有 2 种方案
        // F(3) 则可以走 1+1+1，或者 1+2，又或者 2+1，有 3 种方案
        // F(4) 可以走 1+1+1+1、1+1+2、1+2+1、2+1+1、2+2，有 5 种方案
        // 由此可见，F(n) 是 F(n-1) 和 F(n-2) 的方案之和
        dp[0] = 1, dp[1] = 1, dp[2] = 2;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2]; // F(n) = F(n-1) + F(n-2)
        }
        return dp[n];
    }
};

// ----------------------------------------------------------------------------------------------------

// 矩阵快速幂的解法
// time: 0 ms (100%); rem: 7.23 MB (28.33%)
using LL = long long;
using Matrix = vector<vector<LL> >;

class MatrixSolution {
public:
    static int climbStairs(const int n) {
        Matrix ret = {{1, 1}, {1, 0}};
        const Matrix res = matrix_pow(ret, n);
        return static_cast<int>(res[0][0]);
    }

private:
    static Matrix matrix_pow(Matrix &a, int n) {
        Matrix ret = {{1, 0}, {0, 1}};
        while (n > 0) {
            if ((n & 1) == 1) ret = multiply(ret, a);
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }

    static Matrix multiply(const Matrix &a, const Matrix &b) {
        Matrix c(2, vector<LL>(2));
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }
};

// ----------------------------------------------------------------------------------------------------

// 通项公式
// 因使用了数学计算，受限于指令集支持，效率不好评估
// time: 2 ms (35.16%); rem: 7.22 MB (30.17%)
class GeneralFormulasSolution {
public:
    static int climbStairs(const int n) {
        // 由公式 F(n) = F(n-1) + F(n-2)
        // 假设 F(n) = r^n，带入递归关系有 r^n = r^(n-1) + r^(n-2)
        // 对公式各项除以 r^(n-2)，可以得到特征方程 r^2 = r + 1
        // 求得 x_1 = (1 + sqrt(5)) / 2, x_2 = (1 - sqrt(5)) / 2
        //
        // 设通解为 f(n) = c1 * x1^n + c2 * x2^n
        // 代入初始条件 f(1) = 1, f(2) = 1，得 c1 = 1 / sqrt(5), c2 = -(1 / sqrt(5))
        // 所以我们得到这个递推数列的通项公式：f(n) = (1 / sqrt(5)) * ( ((1 + sqrt(5)) / 2)^n - ((1 - sqrt(5)) / 2)^n )
        const double sqrt5 = sqrt(5);
        const double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
        return static_cast<int>(round(fibn / sqrt5));
    }
};

// ----------------------------------------------------------------------------------------------------

// 何苦难为自己，面向结果编程打表吧
// time: 0 ms (100%); rem: 7.03 MB (58.73%)
static int stair_result[46] = {
    0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657,
    46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352,
    24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903
};

class RopSolution {
public:
    static int climbStairs(const int n) {
        return stair_result[n];
    }
};
