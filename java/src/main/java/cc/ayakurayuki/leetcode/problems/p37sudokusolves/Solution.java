package cc.ayakurayuki.leetcode.problems.p37sudokusolves;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * @author Ayakura Yuki
 * @date 2022/11/22-17:13
 */
public class Solution {

  // region solve (submit parts)

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

  // region visualize (for debugging)

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

  // region self testing

  public static char[][] convertToBoard(int[][] numPad) {
    var board = new char[9][9];
    for (var i = 0; i < 9; i++) {
      for (var j = 0; j < 9; j++) {
        var num = numPad[i][j];
        if (num == 0) {
          board[i][j] = '.';
          continue;
        }
        board[i][j] = Integer.toString(num).toCharArray()[0];
      }
    }
    return board;
  }

  public static void main(String[] args) {
    var numPad = new int[][]{
        {0, 8, 0, 0, 0, 5, 0, 7, 0},
        {0, 0, 0, 0, 7, 0, 2, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 9},
        {8, 5, 0, 3, 0, 4, 0, 0, 7},
        {0, 0, 7, 0, 1, 0, 4, 3, 0},
        {3, 0, 0, 9, 0, 0, 0, 2, 5},
        {0, 0, 0, 0, 0, 3, 0, 0, 0},
        {0, 2, 0, 4, 5, 0, 0, 0, 0},
        {0, 4, 0, 7, 0, 0, 0, 0, 0}
    };
    var board = convertToBoard(numPad);
    new Solution().solveSudoku(board);
    visualize(board);
  }

  // endregion

}
