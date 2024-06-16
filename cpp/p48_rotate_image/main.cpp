//
// Created by 绫仓优希 on 2024-06-16.
//

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
