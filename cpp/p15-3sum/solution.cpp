//
// Created by 绫仓优希 on 2024-09-09.
//

/*
15. 三数之和

https://leetcode.cn/problems/3sum/

给你一个整数数组 nums，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k，
同时还满足 nums[i] + nums[j] + nums[k] == 0。请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：
    输入：nums = [-1,0,1,2,-1,-4]
    输出：[[-1,-1,2],[-1,0,1]]
    解释：
        nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0。
        nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0。
        nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0。
        不同的三元组是 [-1,0,1] 和 [-1,-1,2]。
        注意，输出的顺序和三元组的顺序并不重要。
示例 2：
    输入：nums = [0,1,1]
    输出：[]
    解释：唯一可能的三元组和不为 0。
示例 3：
    输入：nums = [0,0,0]
    输出：[[0,0,0]]
    解释：唯一可能的三元组和为 0。

提示：
  * 3 <= nums.length <= 3000
  * -105 <= nums[i] <= 105

hint 1: So, we essentially need to find three numbers x, y, and z such that they add up to the given value.
        If we fix one of the numbers say x, we are left with the two-sum problem at hand!
hint 2: For the two-sum problem, if we fix one of the numbers, say x, we have to scan the entire array to
        find the next number y, which is value - x where value is the input parameter.
        Can we change our array somehow so that this search becomes faster?
hint 3: The second train of thought for two-sum is, without changing the array, can we use additional space somehow?
        Like maybe a hash map to speed up the search?

相关题目：
  * p16-3sum-closest
 */

/*
这道题首先应该排除使用三重循环枚举三元组的方法。考虑使用三重循环枚举的方法，首先是时间复杂度过高（O(n^3)），其次是会得到 O(n^3) 个三元组
结果，这与题目要求的结果不符，而且还占用空间，空间复杂度上升。考虑到要处理重复三元组的情况，还会引入哈希表去重操作，这又会增加哈希表的空间。
所以需要换一个角度思考这个问题。

如果要保持三重循环的大框架不变，需要做到【有限的遍历】，只要保证：

  * 第二重循环枚举到的值不小于第一重循环的值

  * 第三重循环枚举到的值不小于第二重循环的值

也就是说，只要确保三元组 (a, b, c) 满足 a <= b <= c，能做到这个顺序，就不会出现其他任意的如 (b, c, a) 或者 (c, b, a) 等等模式，
从而减少了重复的三元组。

这就要求我们对原数组进行顺序排序，从而达成最基础的【有限的遍历】的条件。

同时，对于每一重循环，相邻两次枚举的元素不能相同，否则会产生重复的枚举。举个例子：

[ 0, 1, 1, 2, 2, 2, 3 ]
  ^     ^  ^

我们使用三重循环枚举到第一个三元组是 (0, 1, 2)，如果第三重循环继续下一个元素，则又是 (0, 1, 2) 这个三元组，这就叫做【重复】。因此我们
需要将第三重循环跳到下一个不同的元素，在这个例子中是 3，也就是要枚举三元组 (0, 1, 3)。
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    static vector<vector<int> > threeSum(vector<int> &nums) {
        vector<vector<int> > ans;
        const int n = static_cast<int>(nums.size());
        sort(nums.begin(), nums.end()); // 排序，制造便于双指针遍历的顺序数组
        int l = 0, r = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 跳过重复的元素
            l = i + 1, r = n - 1;
            while (l < r) {
                sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    ans.push_back({nums[i], nums[l], nums[r]}); // 命中
                    while (l < r && nums[l] == nums[l + 1]) ++l; // 跳过重复的元素
                    while (l < r && nums[r] == nums[r - 1]) --r; // 跳过重复的元素
                    ++l; // 移动到下一个位置
                    --r; // 移动到下一个位置
                } else if (sum < 0) {
                    ++l; // 移动到下一个位置（因为 sum < 0，左指针右移只会让 sum 尽可能靠近 0）
                } else {
                    --r; // 移动到下一个位置（因为 sum > 0，右指针左移只会让 sum 尽可能靠近 0）
                }
            }
        }
        return ans;
    }
};
