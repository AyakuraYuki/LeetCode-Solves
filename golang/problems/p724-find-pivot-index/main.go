package main

func pivotIndex(nums []int) int {
	var total, sum int
	for _, num := range nums {
		total += num
	}
	for i := 0; i < len(nums); i++ {
		if sum*2+nums[i] == total {
			return i
		}
		sum += nums[i]
	}
	return -1
}
