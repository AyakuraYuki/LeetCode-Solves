//
// Created by 绫仓优希 on 2024-07-01.
//

/*
2401. 最长优雅子数组

https://leetcode.cn/problems/longest-nice-subarray/

> 米哈游第309场周赛

给你一个由 正 整数组成的数组 nums。

如果 nums 的子数组中位于 不同 位置的每对元素按位 与（AND）运算的结果等于 0 ，则称该子数组为 优雅 子数组。

返回 最长 的优雅子数组的长度。

子数组 是数组中的一个 连续 部分。

注意：长度为 1 的子数组始终视作优雅子数组。

示例 1：
    输入：nums = [1,3,8,48,10]
    输出：3
    解释：最长的优雅子数组是 [3,8,48] 。子数组满足题目条件：
        - 3 AND 8 = 0
        - 3 AND 48 = 0
        - 8 AND 48 = 0
        可以证明不存在更长的优雅子数组，所以返回 3 。
示例 2：
    输入：nums = [3,1,5,11,13]
    输出：1
    解释：最长的优雅子数组长度为 1 ，任何长度为 1 的子数组都满足题目条件。

提示：
  * 1 <= nums.length <= 105
  * 1 <= nums[i] <= 109

hint 1: What is the maximum possible length of a nice subarray?
hint 2: The length of the longest nice subarray cannot exceed 30. Why is that?
*/

#include <vector>
using namespace std;

class Solution {
public:
    static int longestNiceSubarray(vector<int> &nums) {
        int ans = 0;
        for (int left = 0, right = 0, mask = 0; right < nums.size(); ++right) {
            while ((mask & nums[right]) != 0) {
                // 右边界值与前面的子数组中存在交集
                mask ^= nums[left++]; // 把左边界值从 mask 中去掉，然后左边界进位
            }
            mask |= nums[right]; // mask 加上当前右边界的值
            ans = max(ans, right - left + 1); // 拿到最新的最长子数组的长度
        }
        return ans;
    }

    // 双指针逆向窗口思想
    // right每次右移都判断下：用nums[right]和[left, right)之间从right - 1开始到left的数字做与（&）判断，
    // 如果不为0，则left右移，直到记录到最近一个相与（&）为0的位置。
    // 记录下此次right - left + 1的值，如此类推，用ans记录每次循环的最大窗口值
    static int longest_nice_subarray_c(vector<int> &nums) {
        int left = 0, right = 0, ans = 0;
        while (right < nums.size()) {
            for (int i = right - 1; i >= left; --i) {
                if ((nums[i] & nums[right]) != 0) left = i + 1;
            }
            ans = max(ans, right - left + 1);
            ++right;
        }
        return ans;
    }
};
