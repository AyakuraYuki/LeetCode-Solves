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
