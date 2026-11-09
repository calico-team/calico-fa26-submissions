#include <bits/stdc++.h>
using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i] within K[i]
 * seconds, and "NO" otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 * K: the maximum number of seconds allowed for each query
 */
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    const int INF = 1000000000;
    const int S = 2 * N;
    auto id = [&](int r, int c, int mode) {
        return (c * N + r) * 2 + mode;
    };
    auto valid = [&](int r, int c, int mode) {
        if (r < 0 || r >= N || c < 0 || c >= M)
            return false;
        char ch = G[r][c];
        return ch == '.' || (ch == 'B' && mode == 0) || (ch == 'R' && mode == 1);
    };
    struct Node {
        int l, r, mid;
        int left = -1, right = -1;
        vector<int> sources;
        vector<int> dist;
    };
    vector<Node> tree;
    tree.reserve(2 * M);
    function<int(int, int)> build = [&](int l, int r) -> int {
        int idx = (int)tree.size();
        tree.emplace_back();
        tree[idx].l = l;
        tree[idx].r = r;
        int mid = (l + r) / 2;
        tree[idx].mid = mid;
        vector<int> sources;
        for (int row = 0; row < N; row++) {
            for (int mode = 0; mode < 2; mode++) {
                if (valid(row, mid, mode)) {
                    sources.push_back(id(row, mid, mode));
                }
            }
        }
        tree[idx].sources = sources;
        int len = (r - l + 1) * S;
        int cnt = (int)sources.size();
        tree[idx].dist.assign((size_t)cnt * len, -1);
        vector<int> q;
        q.reserve(len);
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        for (int si = 0; si < cnt; si++) {
            int* d = tree[idx].dist.data() + (size_t)si * len;
            q.clear();
            int src = sources[si];
            int mode = src & 1;
            int cell = src >> 1;
            int row = cell % N;
            int col = cell / N;
            int sourceLocal = ((col - l) * N + row) * 2 + mode;
            d[sourceLocal] = 0;
            q.push_back(sourceLocal);
            for (int head = 0; head < (int)q.size(); head++) {
                int u = q[head];
                int curMode = u & 1;
                int x = u >> 1;
                int curRow = x % N;
                int curCol = l + x / N;
                int nd = d[u] + 1;
                for (int k = 0; k < 4; k++) {
                    int nr = curRow + dr[k];
                    int nc = curCol + dc[k];
                    if (nc < l || nc > r)
                        continue;
                    if (!valid(nr, nc, curMode))
                        continue;
                    int v = ((nc - l) * N + nr) * 2 + curMode;
                    if (d[v] == -1) {
                        d[v] = nd;
                        q.push_back(v);
                    }
                }
                if (G[curRow][curCol] == '.') {
                    int v = u ^ 1;
                    if (d[v] == -1) {
                        d[v] = nd;
                        q.push_back(v);
                    }
                }
            }
        }
        if (l < mid) {
            int child = build(l, mid - 1);
            tree[idx].left = child;
        }
        if (mid < r) {
            int child = build(mid + 1, r);
            tree[idx].right = child;
        }
        return idx;
    };
    int root = build(0, M - 1);
    auto getLocal = [&](int state, int l) {
        int mode = state & 1;
        int cell = state >> 1;
        int row = cell % N;
        int col = cell / N;
        return ((col - l) * N + row) * 2 + mode;
    };
    auto getDistance = [&](int a, int b) {
        int answer = INF;
        function<void(int)> query = [&](int idx) {
            const Node& node = tree[idx];
            int l = node.l;
            int mid = node.mid;
            int r = node.r;
            int len = (r - l + 1) * S;
            int A = getLocal(a, l);
            int B = getLocal(b, l);
            int cnt = (int)node.sources.size();
            for (int si = 0; si < cnt; si++) {
                const int* d = node.dist.data() + (size_t)si * len;
                int da = d[A];
                int db = d[B];
                if (da == -1 || db == -1)
                    continue;
                answer = min(answer, da + db);
            }
            int ca = (a >> 1) / N;
            int cb = (b >> 1) / N;
            if (ca < mid && cb < mid) {
                if (node.left != -1)
                    query(node.left);
            }
            else if (ca > mid && cb > mid) {
                if (node.right != -1)
                    query(node.right);
            }
        };
        query(root);
        return answer;
    };
    vector<string> ans(Q, "NO");
    for (int i = 0; i < Q; i++) {
        int sr = start[i].first;
        int sc = start[i].second;
        int er = end[i].first;
        int ec = end[i].second;
        int s = id(sr, sc, 0);
        int best = INF;
        for (int mode = 0; mode < 2; mode++) {
            if (!valid(er, ec, mode))
                continue;
            int e = id(er, ec, mode);
            best = min(best, getDistance(s, e));
        }
        ans[i] = (best <= K[i]) ? "YES" : "NO";
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        vector<int> K;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col, k;
            cin >> start_row >> start_col >> end_row >> end_col >> k;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
            K.push_back(k);
        }

        for (string s : solve(N, M, Q, G, start, end, K)) {
            cout << s << '\n';
        }
    }
}