package main

import "fmt"

// 称 startPos -> endPos 是正方向，startPos <- endPos 是负方向，
// 有正方向走 a 步，负方向走 (k - a) 步，可以从 startPos 走到 endPos，
// 则有组合数 C(k,a)，即 k 步里选 a 步走正方向。
//
// 记 distance = abs(startPos - endPos)，
// 则 distance = a - (k - a)，得 a = (distance + k) / 2，
// 所以需要 distance + k 得到偶数，并且 distance <= k，否则走不到 endPos。
//
// 则有 C(i,j) = C(i-1,j) + C(i-1,j-1) 递推式可以求出组合数，组合数中 a 的位置就是最终方案数。

// 给你两个 正 整数 startPos 和 endPos 。最初，你站在 无限 数轴上位置 startPos 处。在一步移动中，你可以向左或者向右移动一个位置。
//
// 给你一个正整数 k ，返回从 startPos 出发、恰好 移动 k 步并到达 endPos 的 不同 方法数目。由于答案可能会很大，返回对 109 + 7 取余 的结果。
//
// 如果所执行移动的顺序不完全相同，则认为两种方法不同。
//
// 注意：数轴包含负整数。
func numberOfWays(startPos int, endPos int, k int) int {
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
	fmt.Println(dp)
	return dp[(distance+k)/2]
}

// 没有优化前，使用二位数组动态规划的流程
//
// 给你两个 正 整数 startPos 和 endPos 。最初，你站在 无限 数轴上位置 startPos 处。在一步移动中，你可以向左或者向右移动一个位置。
//
// 给你一个正整数 k ，返回从 startPos 出发、恰好 移动 k 步并到达 endPos 的 不同 方法数目。由于答案可能会很大，返回对 109 + 7 取余 的结果。
//
// 如果所执行移动的顺序不完全相同，则认为两种方法不同。
//
// 注意：数轴包含负整数。
func numberOfWaysBeforeOptimize(startPos int, endPos int, k int) int {
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
		dp[i][0] = 1
		for j := 1; j <= i; j++ {
			dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 1000000007
		}
	}
	fmt.Println(dp)
	return dp[k][(distance+k)/2]
}
