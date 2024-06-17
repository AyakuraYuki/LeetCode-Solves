/*
2400. 恰好移动 k 步到达某一位置的方法数目

https://leetcode.cn/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/

> 米哈游第309场周赛

给你两个 正 整数 startPos 和 endPos 。最初，你站在 无限 数轴上位置 startPos 处。在一步移动中，你可以向左或者向右移动一个位置。

给你一个正整数 k ，返回从 startPos 出发、恰好 移动 k 步并到达 endPos 的 不同 方法数目。由于答案可能会很大，返回对 109 + 7 取余 的结果。

如果所执行移动的顺序不完全相同，则认为两种方法不同。

注意：数轴包含负整数。

示例 1：
	输入：startPos = 1, endPos = 2, k = 3
	输出：3
	解释：存在 3 种从 1 到 2 且恰好移动 3 步的方法：
		- 1 -> 2 -> 3 -> 2.
		- 1 -> 2 -> 1 -> 2.
		- 1 -> 0 -> 1 -> 2.
		可以证明不存在其他方法，所以返回 3 。
示例 2：
	输入：startPos = 2, endPos = 5, k = 10
	输出：0
	解释：不存在从 2 到 5 且恰好移动 10 步的方法。

提示：
  * 1 <= startPos, endPos, k <= 1000

hint 1: How many steps to the left and to the right do you need to make exactly?
hint 2: Does the order of the steps matter?
hint 3: Use combinatorics to find the number of ways to order the steps.
*/

package main

// 称 startPos -> endPos 是正方向，startPos <- endPos 是负方向，
// 有正方向走 a 步，负方向走 (k - a) 步，可以从 startPos 走到 endPos，
// 则有组合数 C(k,a)，即 k 步里选 a 步走正方向。
//
// 记 distance = abs(startPos - endPos)，
// 则 distance = a - (k - a)，得 a = (distance + k) / 2，
// 所以需要 distance + k 得到偶数，并且 distance <= k，否则走不到 endPos。
//
// 则有 C(i,j) = C(i-1,j) + C(i-1,j-1) 递推式可以求出组合数，组合数中 a 的位置就是最终方案数。
func numberOfWays(startPos int, endPos int, k int) int {
	distance := startPos - endPos // 步数差
	if distance < 0 {
		distance *= -1
	}
	if distance > k || (distance+k)%2 != 0 {
		return 0 // 步数不足以走完距离，或者步数走到距离差一步/多一步，则代表无解法
	}
	// 动态规划
	dp := make([][]int, k+1)
	for i := 0; i < k+1; i++ {
		dp[i] = make([]int, k+1)
	}
	// 求组合数
	for i := 0; i <= k; i++ {
		dp[i][0] = 1 // 任意 i 步数在走 0 步的场合都代表停在原地，所以固定是 1 种走法
		for j := 1; j <= i; j++ {
			// dp[i][j] 表示在第 i 步走 j 步向 endPos 方向的不同方式的数量
			dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 1000000007
		}
	}
	return dp[k][(distance+k)/2]
}

// 优化使用一维数据记忆
func numberOfWaysOptimize(startPos int, endPos int, k int) int {
	distance := startPos - endPos // 步数差
	if distance < 0 {
		distance *= -1
	}
	if distance > k || (distance+k)%2 != 0 {
		return 0 // 步数不足以走完距离，或者步数走到距离差一步/多一步，则代表无解法
	}
	// 动态规划
	dp := make([]int, k+1)
	// 求组合数
	for i := 0; i <= k; i++ {
		dp[0] = 1
		for j := i; j >= 1; j-- {
			dp[j] = (dp[j] + dp[j-1]) % 1000000007
		}
	}
	return dp[(distance+k)/2]
}