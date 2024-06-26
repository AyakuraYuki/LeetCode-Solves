package cc.ayakurayuki.leetcode.problems.p498diagonaltraverse;

/**
 * @author Ayakura Yuki
 * @date 2024/06/26-11:10
 */
public class Solution {

  public int[] findDiagonalOrder(int[][] mat) {
    final int m = mat.length;
    final int n = mat[0].length;
    int[] res = new int[m * n];
    int cursor = 0;
    for (int i = 0; i < m + n - 1; i++) {
      if (i % 2 == 0) {
        // 向右上的方向
        int x = i < m ? i : m - 1; // 区分上下界的获取 x 的开始位置
        int y = i < m ? 0 : i - m + 1; // 区分上下界的获取 y 的开始位置
        while (x >= 0 && y < n) {
          res[cursor++] = mat[x][y];
          --x;
          ++y;
        }
      } else {
        // 向左下的方向
        int x = i < n ? 0 : i - n + 1; // 区分上下界的获取 x 的开始位置
        int y = i < n ? i : n - 1; // 区分上下界的获取 y 的开始位置
        while (x < m && y >= 0) {
          res[cursor++] = mat[x][y];
          ++x;
          --y;
        }
      }
    }
    return res;
  }

}
