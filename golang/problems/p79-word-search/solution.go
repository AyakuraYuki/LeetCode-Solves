/*
79. 单词搜索

https://leetcode.com/problems/word-search/description/

给定一个 m x n 二维字符网格 board 和一个字符串单词 word。如果 word 存在于网格中，返回 true；否则，返回 false。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

示例 1：
	（图片：demo1.jpg）
	输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
	输出：true
示例 2：
	（图片：demo2.jpg）
	输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
	输出：true
示例 3：
	（图片：demo3.jpg）
	输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
	输出：false

提示：
  * m == board.length
  * n = board[i].length
  * 1 <= m, n <= 6
  * 1 <= word.length <= 15
  * board 和 word 仅由大小写英文字母组成

进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？
*/

package p79_word_search

// region solve

func exist(board [][]byte, word string) bool {
	m, n := len(board), len(board[0])
	if m == 0 || n == 0 {
		return false
	}
	words := []byte(word)
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if search(board, m, n, words, 0, i, j) {
				return true
			}
		}
	}
	return false
}

func search(board [][]byte, m, n int, words []byte, cursor, i, j int) bool {
	if cursor == len(words) {
		return true
	}
	if i < 0 || j < 0 || i >= m || j >= n || board[i][j] != words[cursor] {
		return false
	}
	b := board[i][j]
	board[i][j] = '#'
	// searching up/down/left/right
	res := search(board, m, n, words, cursor+1, i-1, j) ||
		search(board, m, n, words, cursor+1, i+1, j) ||
		search(board, m, n, words, cursor+1, i, j-1) ||
		search(board, m, n, words, cursor+1, i, j+1)
	board[i][j] = b
	return res
}

// endregion

// region solve with recursion

func existRecursion(board [][]byte, word string) bool {
	m, n := len(board), len(board[0])
	if m == 0 || n == 0 {
		return false
	}
	visited := make([][]bool, m)
	for i := range visited {
		visited[i] = make([]bool, n)
	}
	words := []byte(word)
	for i := range visited {
		for j := range visited[i] {
			if searchRecursion(board, m, n, visited, words, 0, i, j) {
				return true
			}
		}
	}
	return false
}

func searchRecursion(board [][]byte, m, n int, visited [][]bool, words []byte, cursor, i, j int) bool {
	if cursor == len(words) {
		return true
	}
	if i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || board[i][j] != words[cursor] {
		return false
	}
	visited[i][j] = true
	// searching up/down/left/right
	res := searchRecursion(board, m, n, visited, words, cursor+1, i-1, j) ||
		searchRecursion(board, m, n, visited, words, cursor+1, i+1, j) ||
		searchRecursion(board, m, n, visited, words, cursor+1, i, j-1) ||
		searchRecursion(board, m, n, visited, words, cursor+1, i, j+1)
	visited[i][j] = false
	return res
}

// endregion
