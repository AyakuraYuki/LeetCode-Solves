/*
 * @lc app=leetcode id=37 lang=golang
 *
 * [37] Sudoku Solver
 *
 * https://leetcode.com/problems/sudoku-solver/description/
 *
 * algorithms
 * Hard (36.12%)
 * Total Accepted:    122.5K
 * Total Submissions: 339K
 * Testcase Example:
 * [
 *     ['5','3','.','.','7','.','.','.','.'],
 *     ['6','.','.','1','9','5','.','.','.'],
 *     ['.','9','8','.','.','.','.','6','.'],
 *     ['8','.','.','.','6','.','.','.','3'],
 *     ['4','.','.','8','.','3','.','.','1'],
 *     ['7','.','.','.','2','.','.','.','6'],
 *     ['.','6','.','.','.','.','2','8','.'],
 *     ['.','.','.','4','1','9','.','.','5'],
 *     ['.','.','.','.','8','.','.','7','9']
 * ]
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * A sudoku solution must satisfy all the following rules:
 *
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the digits 1-9 must occur exactly once in each of the 9 3x3
 * sub-boxes of the grid.
 *
 * Empty cells are indicated by the character '.'.
 *
 *
 * A sudoku puzzle...
 *
 * ...and its solution numbers marked in red.
 *
 * Note:
 *
 * The given board contain only digits 1-9 and the character '.'.
 * You may assume that the given Sudoku puzzle will have a single unique
 * solution.
 * The given board size is always 9x9.
 */

package main

import (
	"fmt"
	"strings"
)

// region solve

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

// endregion

// region visualize

func visualize(board [][]byte) {
	for row := 0; row < len(board); row++ {
		if row%3 == 0 {
			fmt.Println("+-------|-------|-------+")
		}
		groups := sliceRow(board[row], 3)
		fmt.Println(fmt.Sprintf("| %s | %s | %s |", strings.Join(groups[0], " "), strings.Join(groups[1], " "), strings.Join(groups[2], " ")))
	}
	fmt.Println("+-------|-------|-------+")
}

func sliceRow(row []byte, fixedSize int) [][]string {
	result := make([][]string, 0)
	if row == nil || len(row) == 0 {
		return result
	}
	for low, high := 0, 0; low < len(row); low = high {
		high = low + fixedSize
		if high > len(row) {
			high = len(row)
		}
		result = append(result, strings.Split(string(row[low:high]), ""))
	}
	return result
}

// endregion

func main() {
	board := [][]byte{
		{byte('5'), byte('3'), byte('.'), byte('.'), byte('7'), byte('.'), byte('.'), byte('.'), byte('.')},
		{byte('6'), byte('.'), byte('.'), byte('1'), byte('9'), byte('5'), byte('.'), byte('.'), byte('.')},
		{byte('.'), byte('9'), byte('8'), byte('.'), byte('.'), byte('.'), byte('.'), byte('6'), byte('.')},
		{byte('8'), byte('.'), byte('.'), byte('.'), byte('6'), byte('.'), byte('.'), byte('.'), byte('3')},
		{byte('4'), byte('.'), byte('.'), byte('8'), byte('.'), byte('3'), byte('.'), byte('.'), byte('1')},
		{byte('7'), byte('.'), byte('.'), byte('.'), byte('2'), byte('.'), byte('.'), byte('.'), byte('6')},
		{byte('.'), byte('6'), byte('.'), byte('.'), byte('.'), byte('.'), byte('2'), byte('8'), byte('.')},
		{byte('.'), byte('.'), byte('.'), byte('4'), byte('1'), byte('9'), byte('.'), byte('.'), byte('5')},
		{byte('.'), byte('.'), byte('.'), byte('.'), byte('8'), byte('.'), byte('.'), byte('7'), byte('9')},
	}
	solveSudoku(board)
	visualize(board)
}
