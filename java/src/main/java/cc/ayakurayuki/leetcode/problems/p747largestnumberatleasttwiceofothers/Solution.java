package cc.ayakurayuki.leetcode.problems.p747largestnumberatleasttwiceofothers;

/**
 * [747] <a href="https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/">Largest Number At Least Twice of Others</a>
 *
 * @author Ayakura Yuki
 * @date Oct 27, 2018 10:33
 */
public class Solution {

  public int dominantIndex(int[] nums) {
    int m1 = -1, m2 = -1, index = -1;
    for (int i = 0; i < nums.length; i++) {
      if (nums[i] > m1) {
        m2 = m1;
        m1 = nums[i];
        index = i;
      } else if (nums[i] > m2) {
        m2 = nums[i];
      }
    }
    return m1 >= m2 * 2 ? index : -1;
  }

}
