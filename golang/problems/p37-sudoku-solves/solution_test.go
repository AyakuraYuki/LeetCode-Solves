package p37_sudoku_solves

import (
	"fmt"
	"strings"
	"testing"
)

func Test_solveSudoku(t *testing.T) {
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
