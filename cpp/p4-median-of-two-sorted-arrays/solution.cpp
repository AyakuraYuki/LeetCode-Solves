//
// Created by 绫仓优希 on 2024-09-05.
//

/*
4. 寻找两个正序数组的中位数

https://leetcode.cn/problems/median-of-two-sorted-arrays/

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。
算法的时间复杂度应该为 O(log(m+n))。

示例 1：
    输入：nums1 = [1,3], nums2 = [2]
    输出：2.00000
    解释：合并数组 = [1,2,3] ，中位数 2
示例 2：
    输入：nums1 = [1,2], nums2 = [3,4]
    输出：2.50000
    解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

提示：
  * nums1.length == m
  * nums2.length == n
  * 0 <= m <= 1000
  * 0 <= n <= 1000
  * 1 <= m + n <= 2000
  * -106 <= nums1[i], nums2[i] <= 106
 */

#include <vector>
using namespace std;

class Solution {
public:
    // 暴力解法：合并两数组再取中间数
    static double findMedianSortedArrays(const vector<int> &nums1, const vector<int> &nums2) {
        const size_t m = nums1.size();
        const size_t n = nums2.size();
        if (m == 0) return n % 2 == 1 ? nums2[n / 2] : (nums2[n / 2 - 1] + nums2[n / 2]) / 2.0;
        if (n == 0) return m % 2 == 1 ? nums1[m / 2] : (nums1[m / 2 - 1] + nums1[m / 2]) / 2.0;

        const size_t max = m + n;
        vector arr(max, 0);
        int i = 0, j = 0, cursor = 0;
        while (i < m && j < n) arr[cursor++] = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];
        while (i < m) arr[cursor++] = nums1[i++];
        while (j < n) arr[cursor++] = nums2[j++];

        return max % 2 == 1 ? arr[max / 2] : (arr[max / 2 - 1] + arr[max / 2]) / 2.0;
    }

    // 不合并数组直接找中位数
    static double find_median_sorted_arrays_no_merge(const vector<int> &nums1, const vector<int> &nums2) {
        const size_t m = nums1.size();
        const size_t n = nums2.size();
        const size_t max = m + n;
        // left 保存上一个循环的结果，right 保存当前循环的结果，这样对于 max 是奇数的情况下，right 就是中位数；max 是偶数的情况下，中位数就是 left 和 right 之和再除 2
        int i = 0, j = 0, left = -1, right = -1;
        // 知道合并数组后的长度 max 后，只需要知道第 (max+1)/2 个数就可以了，如果要遍历的话，只需要遍历 int(max/2)+1 次。
        // max 是偶数时，我们需要知道第 max/2 和 (max/2)+1 这两个数，也是需要遍历 int(max/2)+1 次。
        // 综上所述，循环遍历的边界条件就是 cursor <= max/2
        for (int cursor = 0; cursor <= max / 2; ++cursor) {
            // 窗口移动
            left = right;
            // i 和 j 分别表示 num1 和 num2 的当前位置，如果 i 还没有到达 num1 末尾，并且此时 num1[i] 小于 num2[j]，那么 i 就可以后移；
            // 但是由于 j 也需要判断边界，所以当 j 提前于 i 到达了 num2 的末尾，则应该继续读取 num1 的数字。
            if (i < m && (j >= n || nums1[i] < nums2[j]))
                right = nums1[i++];
            else
                right = nums2[j++];
        }
        return (max & 1) == 0 ? (left + right) / 2.0 : right;
    }

    // 大厂面试思路：结合中位数的定义，切分数组找到中位数
    // 首先理解什么是中位数：一个统计学中的专有名词，代表一个样本、种群或者概率分布中的一个数值，可以将数值集合分为相等的上下两个部分。
    // 所以我们只需要将数组进行切分。
    //
    // 一个长度为 m 的数组，有 0 到 m 的总共 m+1 个切分点：
    // | 0 | 1 | ... | i-1 | i | i+1 |  ...  | m-1 |
    // 0   1   2    ...    i  i+1   i+2 ... m-1    m
    //
    // 我们把数组 A 和 数组 B 分别在 i 和 j 进行切割
    //
    // A:   0 ... i-1 | i i+1 ... m-1
    //       left     i     right
    //
    // B: 0 1 ... j-1 | j j+1 ... n-1
    //       left     j     right
    //
    // 将 i 的左边和 j 的左边组成【左半部分】，i 的右边和 j 的右边组成【右半部分】
    //
    //   * 当 A 和 B 的总长度是偶数，如果我们能保证
    //     * 左半部分长度等于右半部分 i+j = m-i + n-j，即 j = (m+n)/2 - i
    //     * 左半部分最大的值 <= 右半部分最小的值 max(A[i-1], B[j-1]) <= min(A[i], B[j])
    //     那么，中位数就可以表示为 ( max(A[i-1], B[j-1]) + min(A[i], B[j]) ) / 2
    //
    //   * 当 A 和 B 的总长度是奇数，如果我们能保证
    //     * 左半部分的长度比右半部分大1，i+j = m-i + n-j+1，即 j = (m+n+1)/2 - i
    //     * 左半部分最大的值 <= 右半部分最小的值 max(A[i-1], B[j-1]) <= min(A[i], B[j])
    //     那么，中位数就是左半部分最大值，也就是左半部分比右半部分多出的那一个数: max(A[i-1], B[j-1])
    //
    // 上边的第一个条件可以合并为 j = (m+n+1)/2 - i，因为如果 m+n 是偶数，因为是 int 类型，所以 +1 不会影响结果。
    // 当然，由于 0 <= i <= m，为了保证 0 <= j <= n，必须保证 m <= n。
    //
    // m <= n, i < m, j = (m+n+1)/2-i >= (m+m+1)/2-i > (m+m+1)/2-m = 0
    // m <= n, i > 0, j = (m+n+1)/2-i <= (n+n+1)/2-i < (n+n+1)/2 = n
    //
    // 最后一步因为是 int 计算，所以 1/2 = 0
    //
    // 对于第二个条件，奇数和偶数个数的情况是一样的。为了保证 max(A[i-1], B[j-1]) <= min(A[i], B[j])，因为已经有了 A 和 B 都是有序数组的先决条件，
    // 天然存在 A[i-1] <= A[i] 和 B[j-1] <= B[j]，所以只要保证 B[j-1] <= A[i] 和 A[i-1] <= B[j] 即可。
    // 分情况来看：
    //
    //   * B[j-1] > A[i]，并且不越界，应该保证 j != 0，i != m
    //     并且，我们需要增加 i，为了数量平衡还要减少 j。由于公式 j = (m+n+1)/2 - i，m+n 是固定值，那么 i 增大，j 自然会减小
    //
    //   * A[i-1] > B[j]，并且不越界，应该保证 i != 0, j != n
    //     与上面的情况相反，需要减少 i，增大 j
    //
    //   * 上面排除掉边界条件后，还需要单独讨论
    //     * 当 i = 0 或者 j = 0，也就是切点切在两个数组最开始的位置
    //       此时左半部分当 j = 0 时，最大的值就是 A[i-1]；当 i = 0 时，最大的值就是 B[j-1]；右半部分最小值和之前一样。
    //     * 当 i = m 或者 j = n，也就是切在最后面
    //       此时左半部分最大值和之前一样；右半部分当 j = n 时最小值是 A[i]；当 i = m 时最小值就是 B[j]
    //
    // 最后，如何增加 i？当然是使用二分法：每次初始化 i 为中间值，然后反复的做减半找中心，直到找到答案。
    static double find_median_sorted_arrays(const vector<int> &nums1, const vector<int> &nums2) {
        const size_t m = nums1.size();
        const size_t n = nums2.size();
        if (m > n) return find_median_sorted_arrays(nums2, nums1);
        const size_t max = m + n;
        int m_min = 0, m_max = m, i = 0, j = 0;
        while (m_min <= m_max) {
            i = (m_min + m_max) / 2;
            j = (max + 1) / 2 - i;
            if (j != 0 && i != m && nums2[j - 1] > nums1[i]) {
                // i 需要增大
                m_min = i + 1;
            } else if (i != 0 && j != n && nums1[i - 1] > nums2[j]) {
                // i 需要减小
                m_max = i - 1;
            } else {
                // 达到要求，并且将边界条件列出来分别处理
                int max_left = 0;
                if (i == 0) max_left = nums2[j - 1];
                else if (j == 0) max_left = nums1[i - 1];
                else max_left = nums1[i - 1] > nums2[j - 1] ? nums1[i - 1] : nums2[j - 1];
                if ((m + n) % 2 == 1) return max_left; // 奇数不考虑右半边，直接返回找到的中位数

                int min_right = 0;
                if (i == m) min_right = nums2[j];
                else if (j == n) min_right = nums1[i];
                else min_right = nums2[j] < nums1[i] ? nums2[j] : nums1[i];
                return (max_left + min_right) / 2.0; // 偶数的话返回两个数字之和的一半
            }
        }
        return 0.0;
    }
};
