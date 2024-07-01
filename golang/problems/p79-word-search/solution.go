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
