#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node {
    int l, r, mid;
    int left = -1, right = -1;

    // Active states in the middle column
    vector<int> sep;

    // dist[i][local_state] = distance from separator state i
    vector<vector<int>> dist;
};

int N, M;
vector<string> grid;
vector<Node> tree;

// State ID
int id(int r, int c, int mode) {
    return (c * N + r) * 2 + mode;
}

bool active(int r, int c, int mode) {
    char x = grid[r][c];

    if (x == '.') return true;
    if (x == 'B') return mode == 0;
    return mode == 1; // R
}

// Convert a global state into a local index for a node
int local_id(int r, int c, int mode, int left_col) {
    return ((c - left_col) * N + r) * 2 + mode;
}

// Build the divide-and-conquer tree
int build(int l, int r) {
    if (l > r) return -1;

    int node_id = tree.size();
    tree.push_back(Node());

    Node &node = tree[node_id];
    node.l = l;
    node.r = r;
    node.mid = (l + r) / 2;

    // Add all active states in the middle column
    for (int row = 0; row < N; row++) {
        for (int mode = 0; mode < 2; mode++) {
            if (active(row, node.mid, mode)) {
                node.sep.push_back(id(row, node.mid, mode));
            }
        }
    }

    int width = r - l + 1;
    int total_states = width * N * 2;

    node.dist.resize(node.sep.size(),
                     vector<int>(total_states, INF));

    // BFS from every separator state
    for (int s = 0; s < (int)node.sep.size(); s++) {
        int start = node.sep[s];

        int start_mode = start % 2;
        int temp = start / 2;
        int start_row = temp % N;
        int start_col = temp / N;

        queue<array<int, 3>> q;

        int start_local =
            local_id(start_row, start_col, start_mode, l);

        node.dist[s][start_local] = 0;
        q.push({start_row, start_col, start_mode});

        while (!q.empty()) {
            auto [row, col, mode] = q.front();
            q.pop();

            int cur_local = local_id(row, col, mode, l);
            int cur_dist = node.dist[s][cur_local];

            // Move in four directions
            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};

            for (int d = 0; d < 4; d++) {
                int nr = row + dr[d];
                int nc = col + dc[d];

                if (nr < 0 || nr >= N || nc < l || nc > r)
                    continue;

                if (!active(nr, nc, mode))
                    continue;

                int nxt_local =
                    local_id(nr, nc, mode, l);

                if (node.dist[s][nxt_local] == INF) {
                    node.dist[s][nxt_local] = cur_dist + 1;
                    q.push({nr, nc, mode});
                }
            }

            // Spin on a normal tile
            if (grid[row][col] == '.') {
                int new_mode = 1 - mode;

                int nxt_local =
                    local_id(row, col, new_mode, l);

                if (node.dist[s][nxt_local] == INF) {
                    node.dist[s][nxt_local] = cur_dist + 1;
                    q.push({row, col, new_mode});
                }
            }
        }
    }

    // Build children
    int mid = node.mid;

    if (l <= mid - 1)
        tree[node_id].left = build(l, mid - 1);

    if (mid + 1 <= r)
        tree[node_id].right = build(mid + 1, r);

    return node_id;
}

// Find shortest distance between two states
int get_distance(int root,
                 int sr, int sc, int smode,
                 int er, int ec, int emode) {

    int answer = INF;
    int node_id = root;

    while (node_id != -1) {
        Node &node = tree[node_id];

        int s_local =
            local_id(sr, sc, smode, node.l);

        int e_local =
            local_id(er, ec, emode, node.l);

        // Try paths that pass through the separator column
        for (int i = 0; i < (int)node.sep.size(); i++) {
            int a = node.dist[i][s_local];
            int b = node.dist[i][e_local];

            if (a < INF && b < INF) {
                answer = min(answer, a + b);
            }
        }

        // Continue only if both points are on the same side
        if (sc < node.mid && ec < node.mid) {
            node_id = node.left;
        }
        else if (sc > node.mid && ec > node.mid) {
            node_id = node.right;
        }
        else {
            break;
        }
    }

    return answer;
}

void solve() {
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
        tree.reserve(4 * M);

        int root = build(0, M - 1);

        while (Q--) {
            int sr, sc, er, ec;
            long long K;

            cin >> sr >> sc >> er >> ec >> K;

            // Ben always starts in blue mode
            int best = INF;

            // Destination can be reached in any mode
            for (int end_mode = 0; end_mode < 2; end_mode++) {
                if (!active(er, ec, end_mode))
                    continue;

                best = min(
                    best,
                    get_distance(
                        root,
                        sr, sc, 0,
                        er, ec, end_mode
                    )
                );
            }

            cout << (best <= K ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    solve();
    return 0;
}