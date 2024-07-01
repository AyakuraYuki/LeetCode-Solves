package p42_trapping_rain_water

// trap solves Trapping Rain Water using Dynamic Programming
// 只需要遍历一次即可的解法
// 这个算法需要 left 和 right 两个指针分别指向数组的首尾位置，从两边向中间扫描
// 在当前两指针确定的范围内，先比较两头找出较小值
// 如果较小值是 left 指向的值，则从左向右扫描
// 如果较小值是 right 指向的值，则从右向左扫描
// 若遇到的值比当较小值小，则将差值存入结果
// 如遇到的值大，则重新确定新的窗口范围
// 以此类推直至 left 和 right 指针重合
func trap(height []int) int {
	left, right, level, water := 0, len(height)-1, 0, 0
	for left < right {
		var lower int
		if height[left] < height[right] {
			lower = height[left]
			left++
		} else {
			lower = height[right]
			right--
		}
		if level < lower {
			level = lower
		}
		water += level - lower
	}
	return water
}
