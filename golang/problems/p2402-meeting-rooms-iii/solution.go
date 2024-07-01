package p2402_meeting_rooms_iii

import (
	"container/heap"
	"sort"
)

func mostBooked(n int, meetings [][]int) (ans int) {
	count := make([]int, n)  // 统计使用次数，索引号即会议室编号
	idle := make(intHeap, n) // 一开始设所有会议室可用
	for i := 0; i < n; i++ {
		idle[i] = i
	}
	using := busyRooms{}                                                                 // 已用的会议室
	sort.Slice(meetings, func(i, j int) bool { return meetings[i][0] < meetings[j][0] }) // 按照会议开始时间对会议安排进行排序
	for _, m := range meetings {
		start, end := m[0], m[1]
		for len(using) > 0 && using[0].end <= start {
			heap.Push(&idle, heap.Pop(&using).(pair).roomNo) // 有正在使用的会议室并且相应的会议在本场会议开始时间之前，把会议室推入 idle 可用队列
		}
		var roomNo int
		if idle.Len() == 0 {
			p := heap.Pop(&using).(pair) // 没有可用的会议室，按照优先级弹出一个最早结束的会议室，优先级是先按结束时间从早到晚，再按会议室编号从小到大排列
			end += p.end - start         // 更新当前会议的结束时间，即最早结束的那一场会议的结束时间加上本次会议的总用时
			roomNo = p.roomNo            // 标记应该使用的会议室编号
		} else {
			roomNo = heap.Pop(&idle).(int) // 从闲置会议室队列拿到最先可以使用的会议室
		}
		count[roomNo]++ // 对应的会议室增加一次使用次数
		heap.Push(&using, pair{end: end, roomNo: roomNo})
	}

	// 找出被使用次数最多的会议室编号
	for roomNo, c := range count {
		if c > count[ans] {
			ans = roomNo
		}
	}
	return
}

type intHeap []int

func (h intHeap) Len() int           { return len(h) }
func (h intHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h intHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h *intHeap) Push(v any)        { *h = append(*h, v.(int)) }
func (h *intHeap) Pop() any {
	old := *h
	v := old[len(old)-1]
	*h = old[:len(old)-1]
	return v
}

type pair struct{ end, roomNo int }
type busyRooms []pair

func (h busyRooms) Len() int { return len(h) }
func (h busyRooms) Less(i, j int) bool {
	return h[i].end < h[j].end || h[i].end == h[j].end && h[i].roomNo < h[j].roomNo
}
func (h busyRooms) Swap(i, j int) { h[i], h[j] = h[j], h[i] }
func (h *busyRooms) Push(v any)   { *h = append(*h, v.(pair)) }
func (h *busyRooms) Pop() any     { a := *h; v := a[len(a)-1]; *h = a[:len(a)-1]; return v }
