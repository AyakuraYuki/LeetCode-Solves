package p42_trapping_rain_water

import "testing"

func Test_trap(t *testing.T) {
	t.Log(trap([]int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}))
}
