#include <vector>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int> &nums) {
        int total = 0;
        for (const int num: nums) total += num;
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

int main(int argc, char *argv[]) {
}
