/*
724. 寻找数组的中心下标

https://leetcode.cn/problems/find-pivot-index/

给你一个整数数组 nums，请计算数组的 中心下标 。

数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

如果中心下标位于数组最左端，那么左侧数之和视为 0，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。

如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，返回 -1。

示例 1：
    输入：nums = [1, 7, 3, 6, 5, 6]
    输出：3
    解释：中心下标是 3。
        左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11，
        右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。
示例 2：
    输入：nums = [1, 2, 3]
    输出：-1
    解释：数组中不存在满足此条件的中心下标。
示例 3：
    输入：nums = [2, 1, -1]
    输出：0
    解释：中心下标是 0。
        左侧数之和 sum = 0 ，（下标 0 左侧不存在元素），
        右侧数之和 sum = nums[1] + nums[2] = 1 + -1 = 0。

提示：
  * 1 <= nums.length <= 104
  * -1000 <= nums[i] <= 1000

注意：本题与主站 1991 题相同：https://leetcode-cn.com/problems/find-the-middle-index-in-array/
*/

#include <vector>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int> &nums) {
        // 对所有数求和
        int total = 0;
        for (const int num: nums) total += num;
        // 当 next 是中心，那么 next 的左侧之和等于右侧之和
        // 又因为中心值不参与左右计算，所以有 total - next = left_sum + right_sum = 2 * part_sum
        // 用一个 sum 记录中心值左侧数值之和，按公式 2*sum + next = total 来判断 next 是否处于中心
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (sum * 2 + nums[i] == total) {
                return i;
            }
            sum += nums[i];
        }
        return -1;
    }
};
