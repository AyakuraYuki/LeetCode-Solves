//
// Created by 绫仓优希 on 2024-06-17.
//

#include <iostream>
#include <valarray>
#include <vector>

class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        const int distance = std::abs(startPos - endPos);
        if (distance > k || (distance + k) % 2 != 0) {
            return 0;
        }
        std::vector<int> dp;
        dp.reserve(k + 1);
        for (int i = 0; i <= k; ++i) {
            dp[0] = 1;
            for (int j = i; j >= 1; --j) {
                dp[j] = (dp[j] + dp[j - 1]) % 1000000007;
            }
        }
        return dp[(distance + k) / 2];
    }
};

int main(int argc, char *argv[]) {
    auto *solution = new Solution();
    std::cout << solution->numberOfWays(1, 2, 3) << std::endl;
    std::cout << solution->numberOfWays(2, 5, 10) << std::endl;
    std::cout << solution->numberOfWays(2, 5, 9) << std::endl;
}
