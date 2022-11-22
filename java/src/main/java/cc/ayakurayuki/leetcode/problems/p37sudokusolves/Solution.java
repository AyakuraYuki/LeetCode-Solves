package cc.ayakurayuki.leetcode.problems.p37sudokusolves;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * [37] <a href="https://leetcode.com/problems/sudoku-solver/description/">Sudoku Solver</a>
 *
 * <p>algorithms
 * <p>Hard (36.12%)
 * <p>Total Accepted:    122.5K
 * <p>Total Submissions: 339K
 * <p>Testcase Example:
 * <pre>
 * [
 *     ['5','3','.','.','7','.','.','.','.'],
 *     ['6','.','.','1','9','5','.','.','.'],
 *     ['.','9','8','.','.','.','.','6','.'],
 *     ['8','.','.','.','6','.','.','.','3'],
 *     ['4','.','.','8','.','3','.','.','1'],
 *     ['7','.','.','.','2','.','.','.','6'],
 *     ['.','6','.','.','.','.','2','8','.'],
 *     ['.','.','.','4','1','9','.','.','5'],
 *     ['.','.','.','.','8','.','.','7','9']
 * ]
 * </pre>
 *
 * <p>Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * <p>A sudoku solution must satisfy all the following rules:
 *
 * <ol>
 *   <li>Each of the digits 1-9 must occur exactly once in each row.</li>
 *   <li>Each of the digits 1-9 must occur exactly once in each column.</li>
 *   <li>Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.</li>
 * </ol>
 *
 * <p>Empty cells are indicated by the character '.'.
 *
 *
 * <p>A sudoku puzzle...
 *
 * <p>...and its solution numbers marked in red.
 *
 * <p>Note:
 *
 * <p>The given board contain only digits 1-9 and the character '.'.
 * <p>You may assume that the given Sudoku puzzle will have a single unique
 * <p>solution.
 * <p>The given board size is always 9x9.
 *
 * @author Ayakura Yuki
 * @date 2022/11/22-17:13
 */
public class Solution {

  // region solve

  public void solveSudoku(char[][] board) {
    dfs(board, 0, 0);
  }

  public boolean dfs(char[][] board, int row, int col) {
    if (col == board[0].length) {
      row++;
      col = 0;
    }
    if (row == board.length) {
      return true;
    }
    if (board[row][col] != '.') {
      return dfs(board, row, col + 1);
    }
    for (char ch = '1'; ch <= '9'; ch++) {
      if (invalid(board, row, col, ch)) {
        board[row][col] = ch;
        if (dfs(board, row, col + 1)) {
          return true;
        }
        board[row][col] = '.';
      }
    }
    return false;
  }

  public boolean invalid(char[][] board, int row, int col, char ch) {
    for (int i = 0; i < 9; i++) {
      if (board[row][i] == ch || board[i][col] == ch || board[row / 3 * 3 + i / 3][col / 3 * 3 + i % 3] == ch) {
        return false;
      }
    }
    return true;
  }

  // endregion

  // region visualize

  public static void visualize(char[][] board) {
    for (var row = 0; row < board.length; row++) {
      if (row % 3 == 0) {
        System.out.println("+-------|-------|-------+");
      }
      List<List<String>> rowChars = sliceChars(board[row], 3);
      System.out.printf("| %s | %s | %s |%n", String.join(" ", rowChars.get(0)), String.join(" ", rowChars.get(1)), String.join(" ", rowChars.get(2)));
    }
    System.out.println("+-------|-------|-------+");
  }

  public static List<List<String>> sliceChars(char[] chars, int lengthOfGroup) {
    if (chars == null || chars.length == 0) {
      return Collections.emptyList();
    }
    List<String> charsStringList = new ArrayList<>();
    for (char ch : chars) {
      charsStringList.add(String.valueOf(ch));
    }
    List<List<String>> result = new ArrayList<>();
    for (int low = 0, high; low < charsStringList.size(); low = high) {
      high = low + lengthOfGroup;
      if (high > charsStringList.size()) {
        high = charsStringList.size();
      }
      result.add(new ArrayList<>(charsStringList.subList(low, high)));
    }
    return result;
  }

  // endregion

  public static void main(String[] args) {
    var board = new char[][]{
        {'.', '9', '3', '.', '1', '.', '.', '.', '4'},
        {'.', '5', '.', '.', '.', '7', '.', '.', '.'},
        {'.', '.', '1', '4', '.', '.', '.', '.', '.'},
        {'6', '.', '.', '.', '9', '.', '.', '.', '.'},
        {'.', '3', '.', '5', '.', '8', '.', '7', '.'},
        {'.', '.', '.', '.', '7', '.', '.', '.', '9'},
        {'7', '.', '.', '.', '.', '.', '1', '.', '.'},
        {'.', '.', '.', '1', '.', '.', '.', '5', '.'},
        {'5', '.', '.', '.', '4', '.', '.', '6', '.'}
    };
    new Solution().solveSudoku(board);
    visualize(board);
  }

}
