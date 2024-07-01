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
