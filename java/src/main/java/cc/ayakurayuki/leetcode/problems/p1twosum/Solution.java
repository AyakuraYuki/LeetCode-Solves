package cc.ayakurayuki.leetcode.problems.p1twosum;

import java.util.HashMap;
import java.util.Map;

/**
 * @author Ayakura Yuki
 * @date Oct 29, 2018 14:20
 */
public class Solution {

  public int[] twoSum(int[] nums, int target) {
    Map<Integer, Integer> map = new HashMap<>();
    for (int i = 0; i < nums.length; i++) {
      int num = nums[i];
      int complement = target - num;
      if (map.containsKey(complement)) {
        return new int[]{map.get(complement), i};
      }
      map.put(num, i);
    }
    throw new IllegalArgumentException("No two sum solution");
  }

}
