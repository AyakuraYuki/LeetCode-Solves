/*
42. Trapping Rain Water

https://leetcode.com/problems/trapping-rain-water/

Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

Example 1:
(img: https://assets.leetcode.com/uploads/2018/10/22/rainwatertrap.png)
-> [0,1,0,2,1,0,1,3,2,1,2,1]
<- 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
-> [4.2.0.3.2.5]
<- 9


Constraints:
- n == height.length
- 1 <= n <= 2 * 10**4
- 0 <= height[i] <= 10**5
*/

package main

import "fmt"

// region solve

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

// endregion

func main() {
	fmt.Println(trap([]int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}))
}
