package p79_word_search

import "testing"

var cases = []struct {
	board [][]byte
	word  string
	want  bool
}{
	{
		board: [][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
		word:  "ABCCED",
		want:  true,
	},
	{
		board: [][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
		word:  "SEE",
		want:  true,
	},
	{
		board: [][]byte{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}},
		word:  "ABCB",
		want:  false,
	},
}

func Test_exist(t *testing.T) {
	for _, v := range cases {
		get := exist(v.board, v.word)
		if get != v.want {
			t.Fatalf("want %t but get %t", v.want, get)
		}
	}
}

func Test_existRecursion(t *testing.T) {
	for _, v := range cases {
		get := existRecursion(v.board, v.word)
		if get != v.want {
			t.Fatalf("want %t but get %t", v.want, get)
		}
	}
}
