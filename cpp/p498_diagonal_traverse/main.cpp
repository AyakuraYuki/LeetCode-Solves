//
// Created by 绫仓优希 on 2024-06-26.
//

/*
498. 对角线遍历

https://leetcode.cn/problems/diagonal-traverse/

给你一个大小为 m x n 的矩阵 mat，请以对角线遍历的顺序，用一个数组返回这个矩阵中的所有元素。

示例 1：
    （图例：见 puzzle-images/p498-diagonal-traverse/diag1-grid.jpg）
    输入：mat = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[1,2,4,7,5,3,6,8,9]
示例 2：
    输入：mat = [[1,2],[3,4]]
    输出：[1,2,3,4]

提示：
  * m == mat.length
  * n == mat[i].length
  * 1 <= m, n <= 104
  * 1 <= m * n <= 104
  * -105 <= mat[i][j] <= 105
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int> > &mat) {
        const int m = mat.size();
        const int n = mat[0].size();
        vector<int> res;
        // 一个矩阵可以得到的总的对角线条数是这个矩阵的长宽之和再 -1
        for (int i = 0; i < m + n - 1; ++i) {
            if (i % 2 == 0) {
                // 向右上的方向
                int x = i < m ? i : m - 1; // 区分上下界的获取 x 的开始位置
                int y = i < m ? 0 : i - m + 1; // 区分上下界的获取 y 的开始位置
                while (x >= 0 && y < n) {
                    res.emplace_back(mat[x][y]);
                    --x;
                    ++y;
                }
            } else {
                // 向左下的方向
                int x = i < n ? 0 : i - n + 1; // 区分上下界的获取 x 的开始位置
                int y = i < n ? i : n - 1; // 区分上下界的获取 y 的开始位置
                while (x < m && y >= 0) {
                    res.emplace_back(mat[x][y]);
                    ++x;
                    --y;
                }
            }
        }
        return res;
    }
};
