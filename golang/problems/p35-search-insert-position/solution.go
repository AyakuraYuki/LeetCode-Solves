package p35_search_insert_position

func searchInsert(nums []int, target int) int {
	n := len(nums)
	if n == 0 {
		return 0 // 空列表等于直接追加，追加的位置就是 0 位
	}
	// 利用二分法查询应该插入的位置
	left, mid, right := 0, 0, n-1
	for left <= right {
		mid = ((right - left) >> 1) + left // 用到了位移除法
		if nums[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}
	return left
}
