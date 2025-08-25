package solution

// dx和dy两者结合判断行走方向
var (
	dx = []int{0, 0, 1, -1}
	dy = []int{1, -1, 0, 0}
)

type Point struct {
	x, y int
}

func BFS(R, C int, labyrinth [50][50]rune) int {
	var (
		distance [50][50]int
		visited  [50][50]bool
		q        []Point
	)
	for r := 0; r < 50; r++ {
		for c := 0; c < 50; c++ {
			distance[r][c] = -1
		}
	}

	// 出生点
	distance[1][1] = 1
	visited[1][1] = true
	q = append(q, Point{1, 1})

	for len(q) > 0 {
		f := q[0]
		q = q[1:]
		x, y := f.x, f.y
		for i := 0; i < 4; i++ {
			tx, ty := x+dx[i], y+dy[i]
			if tx >= 1 && tx <= R && ty >= 1 && ty <= C && labyrinth[tx][ty] == '.' && !visited[tx][ty] {
				visited[tx][ty] = true
				distance[tx][ty] = distance[x][y] + 1
				q = append(q, Point{tx, ty})
			}
		}
	}

	return distance[R][C]
}
