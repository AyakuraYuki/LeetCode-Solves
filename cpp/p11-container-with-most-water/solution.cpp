//
// Created by 绫仓优希 on 2024-09-09.
//

/*
11. 盛最多水的容器

https://leetcode.cn/problems/container-with-most-water/

给定一个长度为 n 的整数数组 height。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i])。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。

说明：你不能倾斜容器。

示例 1：
    （图片：puzzle-images/p11-container-with-most-water/question_11.jpg）
    输入：[1,8,6,2,5,4,8,3,7]
    输出：49
    解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
示例 2：
    输入：height = [1,1]
    输出：1

提示：
  * n == height.length
  * 2 <= n <= 105
  * 0 <= height[i] <= 104

hint 1: If you simulate the problem, it will be O(n^2) which is not efficient.
hint 2: Try to use two-pointers. Set one pointer to the left and one to the right of the array.
        Always move the pointer that points to the lower line.
hint 3: How can you calculate the amount of water at each step?
 */

#include <vector>
using namespace std;

class Solution {
public:
    static int maxArea(const vector<int> &height) {
        int left = 0, right = static_cast<int>(height.size()) - 1, area = 0, ans = 0;
        while (left < right) {
            // 按漏桶找到最合适的桶高，两桶壁间距 right - left 即桶宽，得到当前桶可容纳最多水量
            area = (height[left] < height[right] ? height[left] : height[right]) * (right - left);
            // 记录最大水量
            ans = ans > area ? ans : area;
            // 进行指针移动
            height[left] <= height[right] ? ++left : --right;
        }
        return ans;
    }
};
