//
// Created by 绫仓优希 on 2024-07-01.
//

/*
56. 合并区间

https://leetcode.cn/problems/merge-intervals/

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：
    输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
    输出：[[1,6],[8,10],[15,18]]
    解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：
    输入：intervals = [[1,4],[4,5]]
    输出：[[1,5]]
    解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

提示：
  * 1 <= intervals.length <= 104
  * intervals[i].length == 2
  * 0 <= starti <= endi <= 104
*/

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > merge(vector<vector<int> > &intervals) {
        if (intervals.empty()) return {};
        // 先以区间开头的数值为基准，对区间进行排序
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0];
        });
        vector<vector<int> > merged;
        for (auto &interval: intervals) {
            // 拿到本区间的左右闭合值
            int left = interval[0], right = interval[1];
            // 插入第一组区间，或者当【末尾区间】的【右闭合】小于【本区间】的【左闭合】时追加本区间
            if (const size_t m = merged.size(); m == 0 || merged[m - 1][1] < left) merged.push_back({left, right});
            // 否则，尝试合并本区间到末尾，因为末尾的区间可能【真包含】本区间
            else merged[m - 1][1] = max(merged[m - 1][1], right);
        }
        return merged;
    }
};
