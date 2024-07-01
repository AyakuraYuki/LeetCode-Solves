//
// Created by 绫仓优希 on 2024-06-16.
//

/*
48. 旋转图像

https://leetcode.cn/problems/rotate-image/

给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

示例 1：
    （图示：puzzle-images/p48-rotate-image/mat1.jpg）
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[[7,4,1],[8,5,2],[9,6,3]]
示例 2：
    （图示：puzzle-images/p48-rotate-image/mat2.jpg）
    输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
    输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

提示：
  * n == matrix.length == matrix[i].length
  * 1 <= n <= 20
  * -1000 <= matrix[i][j] <= 1000
 */

#include <vector>
using namespace std;

//  5  1  9 11      15 13  2  5
//  2  4  8 10  ->  14  3  4  1
// 13  3  6  7      12  6  8  9
// 15 14 12 16      16  7 10 11
class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        const size_t n = matrix.size();
        for (int row = 0; row < n / 2; ++row) {
            for (int col = 0; col < (n + 1) / 2; ++col) {
                const int temp = matrix[row][col];
                matrix[row][col] = matrix[n - 1 - col][row];
                matrix[n - 1 - col][row] = matrix[n - 1 - row][n - 1 - col];
                matrix[n - 1 - row][n - 1 - col] = matrix[col][n - 1 - row];
                matrix[col][n - 1 - row] = temp;
            }
        }
    }
};
