//
// Created by 绫仓优希 on 2024-06-26.
//

/*
747. 至少是其他数字两倍的最大数

https://leetcode.cn/problems/largest-number-at-least-twice-of-others/

给你一个整数数组 nums ，其中总是存在 唯一的 一个最大整数 。
请你找出数组中的最大元素并检查它是否 至少是数组中每个其他数字的两倍。如果是，则返回 最大元素的下标 ，否则返回 -1 。

示例 1：
    输入：nums = [3,6,1,0]
    输出：1
    解释：6 是最大的整数，对于数组中的其他整数，6 至少是数组中其他元素的两倍。6 的下标是 1 ，所以返回 1 。
示例 2：
    输入：nums = [1,2,3,4]
    输出：-1
    解释：4 没有超过 3 的两倍大，所以返回 -1 。

提示：
  * 2 <= nums.length <= 50
  * 0 <= nums[i] <= 100
  * nums 中的最大元素是唯一的

hint 1: Scan through the array to find the unique largest element `m`,
        keeping track of it's index `maxIndex`. Scan through the array
        again. If we find some `x != m` with `m < 2*x`, we should
        return `-1`. Otherwise, we should return `maxIndex`.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int dominantIndex(vector<int> &nums) {
        int m1 = -1, m2 = -1, index = -1; // m1：最大值；m2：第二大值；index：最大值所在索引
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > m1) {
                m2 = m1;
                m1 = nums[i];
                index = i;
            } else if (nums[i] > m2) {
                m2 = nums[i];
            }
        }
        return m1 >= m2 * 2 ? index : -1; // m1 大于或等于 m2 的 2 倍，表示找到了最大值
    }
};
