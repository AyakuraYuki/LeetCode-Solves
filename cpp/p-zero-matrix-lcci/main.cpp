//
// Created by 绫仓优希 on 2024-06-25.
//

/*
面试题 01.08. 零矩阵

https://leetcode.cn/problems/zero-matrix-lcci/

编写一种算法，若M × N矩阵中某个元素为0，则将其所在的行与列清零。

示例 1：
    输入：
        [
            [1,1,1],
            [1,0,1],
            [1,1,1]
        ]
    输出：
        [
            [1,0,1],
            [0,0,0],
            [1,0,1]
        ]
示例 2：
    输入：
        [
            [0,1,2,0],
            [3,4,5,2],
            [1,3,1,5]
        ]
    输出：
        [
            [0,0,0,0],
            [0,4,5,0],
            [0,3,1,0]
        ]

提示：
  * 如果你在找到0时清除了行和列，则可能会清理整个矩阵。在对矩阵进行任何更改之前，首先尝试找到所有的0。
  * 你能只用额外的O(N)空间而不是O(N2)吗？在为0的单元格列表中你真正需要的是什么信息？
  * 你可能需要一些数据存储来维护一个需要清零的行与列的列表。通过使用矩阵本身来存储数据，你是否可以把额外的空间占用减小到O(1)？
 */

#include <vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();
        bool first_col0 = false;

        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) {
                first_col0 = true; // 第 i 行首个数字是 0
            }
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0; // 某一格是 0，标记这一格所在的行首和列首是 0，表示存在 0
                }
            }
        }

        // 反向检索并设置行/列为 0
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) matrix[i][j] = 0;
            }
            if (first_col0) matrix[i][0] = 0;
        }
    }
};
