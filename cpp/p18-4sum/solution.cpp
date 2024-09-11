//
// Created by 绫仓优希 on 2024-09-10.
//

/*
18. 四数之和

https://leetcode.cn/problems/4sum/

给你一个由 n 个整数组成的数组 nums ，和一个目标值 target。
请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]]（若两个四元组元素一一对应，则认为两个四元组重复）：

  * 0 <= a, b, c, d < n
  * a、b、c 和 d 互不相同
  * nums[a] + nums[b] + nums[c] + nums[d] == target

你可以按 任意顺序 返回答案 。

示例 1：
    输入：nums = [1,0,-1,0,-2,2], target = 0
    输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：
    输入：nums = [2,2,2,2,2], target = 8
    输出：[[2,2,2,2]]

提示：
  * 1 <= nums.length <= 200
  * -10^9 <= nums[i] <= 10^9
  * -10^9 <= target <= 10^9
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    static vector<vector<int> > fourSum(vector<int> &nums, const int target) {
        if (nums.size() < 4) return {};

        vector<vector<int> > ans;
        const size_t n = nums.size();
        ranges::sort(nums);

        long long sum = 0;
        size_t l = 0, r = 0;

        for (size_t i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 与前一个数相同，跳过

            for (size_t j = i + 1; j < n; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // 与前一个数相同，跳过

                l = j + 1, r = n - 1;
                while (l < r) {
                    sum = static_cast<long long>(nums[i]) + nums[j] + nums[l] + nums[r];
                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[l], nums[r]});
                        while (l < r && nums[l] == nums[l + 1]) ++l; // 跳过重复
                        while (l < r && nums[r] == nums[r - 1]) --r; // 跳过重复
                        ++l;
                        --r;
                    } else if (sum < target) {
                        ++l;
                    } else {
                        --r;
                    }
                }
            }
        }

        return ans;
    }
};
