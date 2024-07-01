/*
舞蹈链算法
 */

#include <vector>
using namespace std;

// N 代表精准覆盖问题在数独场景下的所有约束条件相应的解决方案数
// 9*9 方格数独的规则是：
// 1. 每个格子只能填一个数字
// 2. 每行每个数字只能填一遍
// 3. 每列每个数字只能填一遍
// 4. 每宫每个数字只能填一遍，一个宫是一个 3*3 的小矩阵
constexpr int N = 9 * 9 * 9 * 4;

class node {
public:
    int u{}, d{}, l{}, r{}; // 上下左右
    int row{}, col{}; // 具体坐标
    int s{}; // col 节点数量
    int h{}; // row 头节点
    int ans{}; // 被选的 row
    node() = default;
};

class DLX {
public:
    vector<vector<int> > a;
    const int n = 9 * 9 * 9, m = 9 * 9 * 4;
    int num{};
    vector<node> nodes;

    explicit DLX(vector<vector<int> > &B) {
        a = B;
        dance();
        B = a;
    }

private:
    void dance() {
        // 初始化节点
        init();
        // 初始化解决方案
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                for (int k = 1; k <= 9; ++k) {
                    if (a[i][j] != k && a[i][j] != 0) continue;
                    const int id = i * 9 * 9 + j * 9 + k;
                    Link(id, i * 9 + j + 1);
                    Link(id, i * 9 + k + 81);
                    Link(id, j * 9 + k + 162);
                    Link(id, (i / 3 * 3 + j / 3) * 9 + k + 243);
                }
            }
        }
        // 开始解决问题
        Dance(0);
    }

    void init() {
        num = m + 1;
        nodes.assign(N, node());
        for (int i = 0; i <= m; ++i) {
            node &it = nodes[i];
            it.l = i - 1; // 左
            it.r = i + 1; // 右
            it.u = it.d = i; // 上下
        }
        nodes[0].l = m;
        nodes[m].r = 0;
    }

    void Link(int r, int c) {
        ++num;
        node &row = nodes[r], &col = nodes[c], &nums = nodes[num];

        nums.row = r;
        nums.col = c;
        ++col.s;

        // node[col.u] <-> nums <-> col
        nums.u = col.u;
        nodes[col.u].d = num;
        col.u = num;
        nums.d = c;

        if (row.h == 0) row.h = nums.l = nums.r = num;
        else {
            node &head = nodes[row.h];
            // node[head.l] <-> nums <-> head
            nums.l = head.l;
            nodes[head.l].r = num;
            head.l = num;
            nums.r = row.h;
        }
    }

    void Remove(int c) {
        const node &col = nodes[c];

        // node[col.l] <-> node[col.r]
        nodes[col.l].r = col.r;
        nodes[col.r].l = col.l;

        // 下右
        for (int i = col.d; i != c; i = nodes[i].d) {
            for (int j = nodes[i].r; j != i; j = nodes[j].r) {
                const node &it = nodes[j];
                //node[it.u] <-> node[it.d]
                nodes[it.d].u = it.u;
                nodes[it.u].d = it.d;
                nodes[it.col].s--;
            }
        }
    }

    void Resume(int c) {
        // node[col.l] -> node[c] <- node[col.r]
        const node &col = nodes[c];
        nodes[col.r].l = c;
        nodes[col.l].r = c;

        //上左
        for (int i = nodes[c].u; i != c; i = nodes[i].u) {
            for (int j = nodes[i].l; j != i; j = nodes[j].l) {
                const node &it = nodes[j];
                //node[it.u] -> node[j] <- node[it.d]
                nodes[it.d].u = j;
                nodes[it.u].d = j;
                nodes[it.col].s++;
            }
        }
    }

    int Dance(int dep) {
        if (nodes[0].r == 0) {
            for (int i = 0; i < dep; ++i) {
                const node &it = nodes[i];
                const int x = (it.ans - 1) / 9 / 9;
                const int y = (it.ans - 1) / 9 % 9;
                const int val = (it.ans - 1) % 9 + 1;
                a[x][y] = val;
            }
            return 1;
        }

        int c = nodes[0].r;
        for (int i = nodes[0].r; i != 0; i = nodes[i].r) {
            if (nodes[i].s == 0 || nodes[c].s == 0) return 0;
            if (nodes[i].s < nodes[c].s) c = i;
        }
        Remove(c);

        for (int i = nodes[c].d; i != c; i = nodes[i].d) {
            node &it = nodes[i];
            nodes[dep].ans = it.row;
            for (int j = nodes[i].r; j != i; j = nodes[j].r) Remove(nodes[j].col);
            if (Dance(dep + 1) == 1) return 1;
            for (int j = nodes[i].l; j != i; j = nodes[j].l) Resume(nodes[j].col);
        }
        Resume(c);

        return 0;
    }
};

class DLXSolution {
public:
    void solveSudoku(vector<vector<char> > &board) {
        // DLX处理数值，把谜题板从【字符板】转换成相应的【数字板】
        vector a(9, vector<int>(9));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                a[i][j] = board[i][j] == '.' ? 0 : board[i][j] - '0'; // 待填入格子设为0，其余设为对应数值
            }
        }
        // DLX算法解决数独
        DLX solver(a);
        // 把结果板转换成字符板，赋给 board
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = static_cast<char>(a[i][j] + '0');
            }
        }
    }
};
