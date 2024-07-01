//
// Created by 绫仓优希 on 2024-06-26.
//

/*
37. 解数独

https://leetcode.cn/problems/sudoku-solver/

编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：
1. 数字 1-9 在每一行只能出现一次。
2. 数字 1-9 在每一列只能出现一次。
3. 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 '.' 表示。

示例 1：
    （图示：puzzle-images/p37-sudoku-solves/input.png）
    输入：board = [
        ["5","3",".",".","7",".",".",".","."],
        ["6",".",".","1","9","5",".",".","."],
        [".","9","8",".",".",".",".","6","."],
        ["8",".",".",".","6",".",".",".","3"],
        ["4",".",".","8",".","3",".",".","1"],
        ["7",".",".",".","2",".",".",".","6"],
        [".","6",".",".",".",".","2","8","."],
        [".",".",".","4","1","9",".",".","5"],
        [".",".",".",".","8",".",".","7","9"]
    ]
    （图示：puzzle-images/p37-sudoku-solves/output.png）
    输出：[
        ["5","3","4","6","7","8","9","1","2"],
        ["6","7","2","1","9","5","3","4","8"],
        ["1","9","8","3","4","2","5","6","7"],
        ["8","5","9","7","6","1","4","2","3"],
        ["4","2","6","8","5","3","7","9","1"],
        ["7","1","3","9","2","4","8","5","6"],
        ["9","6","1","5","3","7","2","8","4"],
        ["2","8","7","4","1","9","6","3","5"],
        ["3","4","5","2","8","6","1","7","9"]
    ]
    解释：输入的数独如上图所示，唯一有效的解决方案如下所示：

提示：
  * board.length == 9
  * board[i].length == 9
  * board[i][j] 是一位数字或者 '.'
  * 题目数据 保证 输入数独仅有一个解
 */

#include <vector>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        dfs(board, 0, 0);
    }

private:
    // 递归的回溯法
    static bool dfs(vector<vector<char> > &board, int row, int col) {
        if (col == board[0].size()) {
            ++row;
            col = 0;
        }
        if (row == board.size()) return true;
        if (board[row][col] != '.') return dfs(board, row, col + 1);
        for (char ch = '1'; ch <= '9'; ++ch) {
            if (invalid(board, row, col, ch)) {
                board[row][col] = ch;
                if (dfs(board, row, col + 1)) return true;
                board[row][col] = '.';
            }
        }
        return false;
    }

    static bool invalid(const vector<vector<char> > &board, const int row, const int col, const char ch) {
        for (int i = 0; i < 9; ++i) {
            if (board[row][i] == ch || board[i][col] == ch || board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == ch)
                return false;
        }
        return true;
    }
};
