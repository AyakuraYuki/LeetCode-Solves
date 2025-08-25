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
		R, C      int      // row, col
		labyrinth [][]rune // labyrinth characters, '.' means visitable, '#' means blocked
	)

	fmt.Print("Enter Row and Col, use space to separate two arguments: ")

	_, err := fmt.Scan(&R, &C)
	if err != nil {
		panic(err)
	}

	labyrinth = make([][]rune, R)
	for i := range labyrinth {
		labyrinth[i] = make([]rune, C)
	}

	fmt.Println("Enter labyrinth, each row as a string, no space needed:")
	scanner := bufio.NewScanner(os.Stdin)

	for r := 0; r < R; r++ {
		fmt.Printf("Row %d: ", r+1)
		if scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if len(line) != C {
				panic(fmt.Sprintf("Row %d should have exactly %d characters, got %d", r+1, C, len(line)))
			}
			labyrinth[r] = []rune(line)
		} else {
			panic("Failed to read input")
		}
	}

	ans := solution.BFS(R, C, labyrinth)
	fmt.Println(ans)
}
