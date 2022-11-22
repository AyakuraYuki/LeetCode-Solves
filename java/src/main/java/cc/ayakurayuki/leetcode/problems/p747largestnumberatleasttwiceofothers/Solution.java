package cc.ayakurayuki.leetcode.problems.p747largestnumberatleasttwiceofothers;

/**
 * [747] <a href="https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/">Largest Number At Least Twice of Others</a>
 *
 * @author Ayakura Yuki
 * @date Oct 27, 2018 10:33
 */
public class Solution {

  public int dominantIndex(int[] nums) {
    int res = 0, largest = nums[0];
    for (int i = 1; i < nums.length; i++) {
      if (nums[i] > largest) {
        if (nums[i] >= largest * 2) {
          res = i;
        } else {
          res = -1;
        }
        largest = nums[i];
      } else {
        if (largest < nums[i] * 2) {
          res = -1;
        }
      }
    }

    return res;
  }

}
