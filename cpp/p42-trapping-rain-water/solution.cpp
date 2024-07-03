//
// Created by 绫仓优希 on 2024-07-01.
//

/*
42. 接雨水

https://leetcode.cn/problems/trapping-rain-water/

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例 1：
    （示例图片见 puzzle-images/p42-trapping-rain-water/demo1-img.png）
    输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
    输出：6
    解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
示例 2：
    输入：height = [4,2,0,3,2,5]
    输出：9

提示：
  - n == height.length
  - 1 <= n <= 2 * 104
  - 0 <= height[i] <= 105
*/

#include <vector>
using namespace std;

class Solution {
public:
    // 只需要遍历一次即可的解法
    // 这个算法需要 left 和 right 两个指针分别指向数组的首尾位置，从两边向中间扫描
    // 在当前两指针确定的范围内，先比较两头找出较小值
    // 如果较小值是 left 指向的值，则从左向右扫描
    // 如果较小值是 right 指向的值，则从右向左扫描
    // 若遇到的值比当较小值小，则将差值存入结果
    // 如遇到的值大，则重新确定新的窗口范围
    // 以此类推直至 left 和 right 指针重合
    static int trap(const vector<int> &height) {
        int left = 0, right = height.size() - 1, level = 0, water = 0;
        while (left < right) {
            int lower;
            if (height[left] < height[right]) {
                lower = height[left];
                ++left;
            } else {
                lower = height[right];
                --right;
            }
            if (level < lower) level = lower;
            water += level - lower;
        }
        return water;
    }
};
