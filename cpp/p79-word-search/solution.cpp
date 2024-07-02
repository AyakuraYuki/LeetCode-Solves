//
// Created by 绫仓优希 on 2024-07-01.
//

/*
79. 单词搜索

https://leetcode.com/problems/word-search/description/

给定一个 m x n 二维字符网格 board 和一个字符串单词 word。如果 word 存在于网格中，返回 true；否则，返回 false。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

示例 1：
    （图片：puzzle-images/p79-word-search/demo1.jpg）
    输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    输出：true
示例 2：
    （图片：puzzle-images/p79-word-search/demo2.jpg）
    输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
    输出：true
示例 3：
    （图片：puzzle-images/p79-word-search/demo3.jpg）
    输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
    输出：false

提示：
  * m == board.length
  * n = board[i].length
  * 1 <= m, n <= 6
  * 1 <= word.length <= 15
  * board 和 word 仅由大小写英文字母组成

进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？
*/

#include <vector>
using namespace std;

class Solution {
public:
    static bool exist(vector<vector<char> > &board, string word) {
        if (board.empty()) return false;
        const size_t m = board.size(), n = board[0].size();
        // 扫描矩阵找到符合 word 的起点
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (search(board, m, n, word, 0, i, j)) return true;
            }
        }
        return false;
    }

private:
    static bool search(vector<vector<char> > &board, const size_t m, const size_t n,
                       string &word, const int cursor, const int i, const int j) {
        // 在递归的过程中，游标达到了 word 长度，说明匹配到了 word
        if (cursor == word.size()) return true;
        // 递归的过程中越界了，说明匹配失败
        // 或者作为上一次游标的 上/下/左/右 时，与当前游标对应的 word 的字母不同，说明匹配中断
        if (i < 0 || j < 0 || i >= m || j >= n || board[i][j] != word[cursor]) return false;
        // 标记当前字符已被检索
        const char b = board[i][j];
        board[i][j] = '#';
        // 搜索 上/下/左/右，尝试找到合适的字母，任何一个分叉返回true就表示找到 word 了
        const bool res = search(board, m, n, word, cursor + 1, i - 1, j) ||
                         search(board, m, n, word, cursor + 1, i + 1, j) ||
                         search(board, m, n, word, cursor + 1, i, j - 1) ||
                         search(board, m, n, word, cursor + 1, i, j + 1);
        // 还原当前字符
        board[i][j] = b;
        return res;
    }
};
