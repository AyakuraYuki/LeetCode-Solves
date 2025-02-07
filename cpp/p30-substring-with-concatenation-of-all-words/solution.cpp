//
// Created by 绫仓优希 on 2025-02-07.
//

/*
30. 串联所有单词的子串

https://leetcode.cn/problems/substring-with-concatenation-of-all-words/

给定一个字符串 s 和一个字符串数组 words。words 中所有字符串“长度相同”。

s 中的“串联子串”是指一个包含 words 中所有字符串以任意顺序排列连接起来的子串。

- 例如，如果 words = ["ab","cd","ef"]，那么 "abcdef"，"abefcd"，"cdabef"，"cdefab"，"efabcd" 和 "efcdab" 都是串联子串。
  "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。

返回所有串联子串在 s 中的开始索引。你可以以“任意顺序”返回答案。

示例 1：
    输入：s = "barfoothefoobarman", words = ["foo","bar"]
    输出：[0,9]
    解释：
        因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
        子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
        子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
        输出顺序无关紧要。返回 [9,0] 也是可以的。
示例 2：
    输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
    输出：[]
    解释：
        因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
        s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
        所以我们返回一个空数组。
示例 3：
    输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
    输出：[6,9,12]
    解释：
        因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
        子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
        子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
        子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。

提示：
  * 1 <= s.length <= 104
  * 1 <= words.length <= 5000
  * 1 <= words[i].length <= 30
  * words[i] 和 s 由小写英文字母组成
 */

#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(const string &s, const vector<string> &words) {
        const int word_len = words[0].size(); // 单词长度
        const int word_count = words.size(); // 单词数量
        // required_len: 所需长度
        if (const int required_len = word_len * word_count; s.size() < required_len) { return {}; }

        unordered_map<string, int> required_map; // 记录每个单词所需要出现的次数
        for (const auto &word: words) required_map[word]++;

        vector<int> res;
        // 滑动窗口起点
        for (int i = 0; i < word_len; i++) {
            int left = i, right = i, count = 0;
            unordered_map<string, int> seen_map;
            // 外层循环控制窗口右边界，每次增长一个单词长度
            for (; right < s.size() - word_len + 1; right += word_len) {
                string right_str = s.substr(right, word_len);
                seen_map[right_str]++;
                count++;

                if (required_map.find(right_str) != required_map.end()) {
                    // 当前单词虽然是所需单词，但已经超过所需次数，需要缩减左窗口，直到单词数符合要求
                    while (seen_map[right_str] > required_map[right_str]) {
                        string left_str = s.substr(left, word_len);
                        seen_map[left_str]--;
                        count--;
                        left += word_len;
                    }
                } else {
                    // 当前单词不是所需单词，左指针跳到这里，重新开始向后滑动
                    seen_map.clear();
                    count = 0;
                    left = right + word_len;
                }

                // 如果当前窗口内的单词数等于 words 内的单词数，则找到一个结果
                if (count == word_count) res.push_back(left);
            }
        }

        return res;
    }
};

// Boyer-Moore 算法
class BoyerMooreSolution {
public:
    vector<int> findSubstring(const string &s, const vector<string> &words) {
        const int n = s.size(), m = words.size(), w = words[0].size();
        vector<int> ans; // 结果集

        unordered_map<string, int> dict, cmp; // dict: 单词所需出现次数; cmp: 找到记录
        for (const auto &word: words) dict[word]++;

        if (dict.size() == 1) {
            // Boyer-Moore 算法在字典大小是 1 时退化，特殊处理
            const string target = views::join(words) | ranges::to<string>();
            for (int pos = 0; (pos = s.find(target, pos)) != string::npos; pos++) ans.push_back(pos);
            return ans;
        }

        for (int start: views::iota(0, w)) {
            for (int i = start, j; i <= n - w * m; i += w) {
                for (j = i + w * (m - 1); j >= i; j -= w) {
                    // 这里的 j -= w 倒序匹配决定了亚线性的复杂度
                    string str = s.substr(j, w);
                    if (!dict.count(str) || dict[str] == cmp[str]) break;
                    cmp[str]++;
                    if (j == i) {
                        ans.push_back(j);
                        break;
                    }
                }
                i = j;
                cmp.clear();
            }
        }

        return ans;
    }
};

int main(int argc, char *argv[]) {
    auto res = Solution().findSubstring("barfoothefoobarman", {"foo", "bar"});
    auto step = 1;
}
