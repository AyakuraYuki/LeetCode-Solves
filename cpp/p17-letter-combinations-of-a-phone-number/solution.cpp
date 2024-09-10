//
// Created by 绫仓优希 on 2024-09-10.
//

/*
17. 电话号码的字母组合

https://leetcode.cn/problems/letter-combinations-of-a-phone-number/

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

（图片：puzzle-images/p17-letter-combinations-of-a-phone-number/200px-telephone-keypad2svg.png）

示例 1：
    输入：digits = "23"
    输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：
    输入：digits = ""
    输出：[]
示例 3：
    输入：digits = "2"
    输出：["a","b","c"]

提示：
  * 0 <= digits.length <= 4
  * digits[i] 是范围 ['2', '9'] 的一个数字。
 */

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    static vector<string> letterCombinations(const string &digits) {
        if (digits.empty()) return {};
        vector<string> ans;
        back_tracking(digits, ans, 0, ""); // 从开头扫描
        return ans;
    }

private:
    static void back_tracking(const string &digits, vector<string> &ans, const int index, string s) {
        if (index == digits.size()) {
            // 检索到最后一个字符，回溯
            ans.push_back(s);
            s.clear();
            return;
        }
        for (const auto letters = load_letters(digits[index]); const char letter: letters) {
            s.push_back(letter); // 填充
            back_tracking(digits, ans, index + 1, s); // 递归下一层
            s.pop_back(); // 回溯
        }
    }

    static vector<char> load_letters(const char digit) {
        switch (digit) {
            case '2': return {'a', 'b', 'c'};
            case '3': return {'d', 'e', 'f'};
            case '4': return {'g', 'h', 'i'};
            case '5': return {'j', 'k', 'l'};
            case '6': return {'m', 'n', 'o'};
            case '7': return {'p', 'q', 'r', 's'};
            case '8': return {'t', 'u', 'v'};
            case '9': return {'w', 'x', 'y', 'z'};
            default: return {};
        }
    }
};

// 评论区的【队列法】
// 队列法的思路是，先放入第一个层级的字母，然后在每一个层级，提出队列头部的字符，追加当前层级的字母并追加到队尾
// 例如 digits = "23"，第一层先放入 a, b, c，然后再第二层级，提出 a 再追加 d, e, f，放入 ad, ae, af，
// 再把 b 提出，追加 d, e, f，放入 bd, be, bf
// 如此一来，每次填充都是对上一层的组合追加字母，既不会重复也保证了追加的顺序
class QueueSolution {
public:
    static vector<string> letter_combinations(const string &digits) {
        if (digits.empty()) return {};

        // 键盘
        const unordered_map<char, vector<char> > keyboard{
            {'2', {'a', 'b', 'c'}},
            {'3', {'d', 'e', 'f'}},
            {'4', {'g', 'h', 'i'}},
            {'5', {'j', 'k', 'l'}},
            {'6', {'m', 'n', 'o'}},
            {'7', {'p', 'q', 'r', 's'}},
            {'8', {'t', 'u', 'v'}},
            {'9', {'w', 'x', 'y', 'z'}},
        };

        vector<string> ans{""};
        ans.reserve(150); // 减少扩容

        for (const char digit: digits) {
            const int n = static_cast<int>(ans.size());
            for (int i = 0; i < n; ++i) {
                string s = ans[0]; // 首个元素
                ans.erase(ans.begin()); // 先剔除首个元素
                for (auto &k: keyboard.at(digit)) {
                    ans.push_back(s + k); // 队列追加新的组合
                }
            }
        }

        return ans;
    }
};
