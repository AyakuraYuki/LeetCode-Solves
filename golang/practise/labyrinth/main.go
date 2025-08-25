package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"

	"github.com/AyakuraYuki/leetcode-golang-solutions/practise/labyrinth/internal/solution"
)

func main() {
	var (
		R, C      int          // row, col
		labyrinth [50][50]rune // labyrinth characters, '.' means visitable, '#' means blocked
	)

	fmt.Print("Enter Row and Col, use space to separate two arguments: ")

	_, err := fmt.Scan(&R, &C)
	if err != nil {
		panic(err)
	}

	fmt.Println("Enter labyrinth, each row as a string, no space needed:")
	scanner := bufio.NewScanner(os.Stdin)

	for r := 1; r <= R; r++ {
		fmt.Printf("Row %d: ", r+1)
		if scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if len(line) != C {
				panic(fmt.Sprintf("Row %d should have exactly %d characters, got %d", r+1, C, len(line)))
			}
			for c := 1; c <= len(line); c++ {
				labyrinth[r][c] = rune(line[c-1])
			}
		} else {
			panic("Failed to read input")
		}
	}

	ans := solution.BFS(R, C, labyrinth)
	fmt.Println(ans)
}
