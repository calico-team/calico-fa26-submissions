
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node {
    int l, r, mid;
    int left = -1, right = -1;

    // Global state IDs for active states in the middle column.
    vector<int> sep;

    // dist[i * V + p] = distance from sep[i] to local state p.
    vector<int> dist;
};

int N, M;
vector<string> grid;
vector<Node> tree;

bool active(int r, int c, int mode) {
    char ch = grid[r][c];

    if (ch == '.') return true;
    if (ch == 'B') return mode == 0;
    return mode == 1; // R
}

int globalID(int r, int c, int mode) {
    return (c * N + r) * 2 + mode;
}

int build(int l, int r) {
    int id = (int)tree.size();
    tree.emplace_back();

    int mid = (l + r) / 2;

    tree[id].l = l;
    tree[id].r = r;
    tree[id].mid = mid;

    // Collect every active state in the middle column.
    for (int row = 0; row < N; row++) {
        for (int mode = 0; mode < 2; mode++) {
            if (active(row, mid, mode)) {
                tree[id].sep.push_back(globalID(row, mid, mode));
            }
        }
    }

    int width = r - l + 1;
    int V = width * N * 2;
    int S = (int)tree[id].sep.size();

    tree[id].dist.assign(S * V, INF);

    auto localID = [&](int row, int col, int mode) {
        return ((col - l) * N + row) * 2 + mode;
    };

    // Run BFS from each separator state, restricted to [l, r].
    vector<int> d(V);
    vector<int> q;
    q.reserve(V);

    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    for (int si = 0; si < S; si++) {
        fill(d.begin(), d.end(), INF);
        q.clear();

        int startGlobal = tree[id].sep[si];
        int cell = startGlobal / 2;
        int mode = startGlobal % 2;

        int row = cell % N;
        int col = cell / N;

        int start = localID(row, col, mode);

        d[start] = 0;
        q.push_back(start);

        for (int head = 0; head < (int)q.size(); head++) {
            int u = q[head];

            int currentMode = u % 2;
            int x = u / 2;
            int currentRow = x % N;
            int currentCol = l + x / N;

            auto relax = [&](int nr, int nc, int nm) {
                if (nr < 0 || nr >= N) return;
                if (nc < l || nc > r) return;
                if (!active(nr, nc, nm)) return;

                int v = localID(nr, nc, nm);

                if (d[v] == INF) {
                    d[v] = d[u] + 1;
                    q.push_back(v);
                }
            };

            // Spin: possible only on a normal tile.
            if (grid[currentRow][currentCol] == '.') {
                relax(currentRow, currentCol, 1 - currentMode);
            }

            // Move one tile in the four cardinal directions.
            for (int k = 0; k < 4; k++) {
                relax(
                    currentRow + dr[k],
                    currentCol + dc[k],
                    currentMode
                );
            }
        }

        copy(
            d.begin(),
            d.end(),
            tree[id].dist.begin() + (size_t)si * V
        );
    }

    // Recursively build the intervals excluding the separator column.
    if (l < mid) {
        tree[id].left = build(l, mid - 1);
    }

    if (mid < r) {
        tree[id].right = build(mid + 1, r);
    }

    return id;
}

void answerQuery(
    int id,
    int sr, int sc,
    int tr, int tc,
    int &best
) {
    const Node &node = tree[id];

    int l = node.l;
    int mid = node.mid;
    int width = node.r - node.l + 1;
    int V = width * N * 2;

    auto localID = [&](int row, int col, int mode) {
        return ((col - l) * N + row) * 2 + mode;
    };

    // Ben starts in blue mode.
    int start = localID(sr, sc, 0);

    // Try every possible state in the separator column.
    for (int si = 0; si < (int)node.sep.size(); si++) {
        int base = si * V;

        int ds = node.dist[base + start];

        if (ds == INF || ds >= best) continue;

        // The destination can be reached in either mode,
        // provided its tile is active in that mode.
        for (int mode = 0; mode < 2; mode++) {
            if (!active(tr, tc, mode)) continue;

            int target = localID(tr, tc, mode);
            int dt = node.dist[base + target];

            if (dt != INF) {
                best = min(best, ds + dt);
            }
        }
    }

    // If both endpoints are in the same child interval,
    // also search for a path that avoids this separator.
    if (sc < mid && tc < mid && node.left != -1) {
        answerQuery(node.left, sr, sc, tr, tc, best);
    }
    else if (sc > mid && tc > mid && node.right != -1) {
        answerQuery(node.right, sr, sc, tr, tc, best);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int Q;
        cin >> N >> M >> Q;

        grid.resize(N);

        for (int i = 0; i < N; i++) {
            cin >> grid[i];
        }

        tree.clear();
        tree.reserve(2 * M);

        int root = build(0, M - 1);

        while (Q--) {
            int rs, cs, re, ce;
            int K;

            cin >> rs >> cs >> re >> ce >> K;

            int best = INF;

            answerQuery(root, rs, cs, re, ce, best);

            cout << (best <= K ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
