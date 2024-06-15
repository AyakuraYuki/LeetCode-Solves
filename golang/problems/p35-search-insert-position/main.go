package main

func searchInsert(nums []int, target int) int {
	n := len(nums)
	if n == 0 {
		return 0 // 空列表等于直接追加，追加的位置就是 0 位
	}
	// 利用二分法查询应该插入的位置
	var left, mid int
	right := n - 1
	for left <= right {
		mid = left + (right-left)/2
		if v := nums[mid]; v == target {
			return mid // 搜索到 target 返回 mid 作为命中索引
		} else if v < target {
			left = mid + 1
		} else { // nums[mid] > target
			right = mid - 1
		}
	}
	return left
}
