package cc.ayakurayuki.leetcode.problems.p724findpivotindex;

/**
 * [724] <a href="https://leetcode.com/problems/find-pivot-index/description/">Find Pivot Index</a>
 *
 * @author Ayakura Yuki
 * @date Oct 26, 2018 17:39
 */
public class Solution {

  public int pivotIndex(int[] nums) {
    int sum = 0;
    for (int num : nums) {
      sum += num;
    }
    int cursor = 0;
    for (int i = 0; i < nums.length; i++) {
      if (sum - nums[i] == cursor * 2) {
        return i;
      }
      cursor += nums[i];
    }
    return -1;
  }

}
