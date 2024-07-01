//
// Created by 绫仓优希 on 2024-07-01.
//

/*
14. 最长公共前缀

https://leetcode.cn/problems/longest-common-prefix/description/

编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。

示例 1：
    输入：strs = ["flower","flow","flight"]
    输出："fl"
示例 2：
    输入：strs = ["dog","racecar","car"]
    输出：""
    解释：输入不存在公共前缀。

提示：
  * 1 <= strs.length <= 200
  * 0 <= strs[i].length <= 200
  * strs[i] 仅由小写英文字母组成
 */

#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty()) return "";
        if (strs.size() == 1) return strs[0];

        size_t min_len = strs[0].size();
        for (const auto &str: strs) {
            if (str.size() < min_len) min_len = str.size();
        }

        int low = 0, high = min_len;
        while (low < high) {
            int mid = (high - low + 1) / 2 + low;
            if (is_common_prefix(strs, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        return strs[0].substr(0, low);
    }

private:
    // 采用逐字比较来减轻由 substr 带来的复杂度
    static bool is_common_prefix(const vector<string> &strs, const int len) {
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = 0; j < len; ++j) {
                if (strs[0][j] != strs[i][j]) return false;
            }
        }
        return true;
    }
};
