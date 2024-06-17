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

package main

func longestNiceSubarray(nums []int) int {
	n := len(nums)
	if n <= 1 {
		return n
	}
	var (
		ans  int // 最长子数组长度
		mask int // 上一次检查的结果
		left int // 左边界
	)
	for right, v := range nums {
		for mask&v > 0 {
			// 右边界值与前面的子数组中存在交集
			mask ^= nums[left] // 把左边界值从 mask 中去掉
			left++             // 然后左边界进位
		}
		mask |= v                    // mask 加上当前右边界的值
		ans = max(ans, right-left+1) // 拿到最新的最长子数组的长度
	}
	return ans
}

// 爆破求解
func longestNiceSubarrayExhaustive(nums []int) int {
	n := len(nums)
	if n <= 1 {
		return n
	}
	var ans int
	for right, v := range nums {
		left := right - 1
		for ; left >= 0 && nums[left]&v == 0; left-- {
			v |= nums[left]
		}
		ans = max(ans, right-left)
	}
	return ans
}