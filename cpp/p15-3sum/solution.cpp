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
