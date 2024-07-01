package p37_sudoku_solves

// solution
func solveSudoku(board [][]byte) {
	dfs(board, 0, 0)
}

func dfs(board [][]byte, row, col int) bool {
	if col == len(board[0]) {
		row++
		col = 0
	}
	if row == len(board) {
		return true
	}
	if board[row][col] != '.' {
		return dfs(board, row, col+1)
	}
	for ch := '1'; ch <= '9'; ch++ {
		if invalid(board, row, col, byte(ch)) {
			board[row][col] = byte(ch)
			if dfs(board, row, col+1) {
				return true
			}
			board[row][col] = '.'
		}
	}
	return false
}

func invalid(board [][]byte, row, col int, ch byte) bool {
	for i := 0; i < 9; i++ {
		if board[row][i] == ch || board[i][col] == ch || board[row/3*3+i/3][col/3*3+i%3] == ch {
			return false
		}
	}
	return true
}
