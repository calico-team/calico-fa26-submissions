
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node {
    int l, r, mid;
    int left = -1, right = -1;
    vector<vector<int>> dist;
};

int N, M;
vector<string> grid;
vector<Node> nodes;

bool valid(int r, int c, int mode) {
    if (r < 0 || r >= N || c < 0 || c >= M)
        return false;

    char ch = grid[r][c];

    return ch == '.' ||
           (ch == 'B' && mode == 0) ||
           (ch == 'R' && mode == 1);
}

int indexOf(int r, int c, int mode, int l) {
    return ((c - l) * N + r) * 2 + mode;
}

int build(int l, int r) {
    int id = nodes.size();
    nodes.emplace_back();

    nodes[id].l = l;
    nodes[id].r = r;
    nodes[id].mid = (l + r) / 2;

    int mid = nodes[id].mid;
    int states = (r - l + 1) * N * 2;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int row = 0; row < N; row++) {
        for (int mode = 0; mode < 2; mode++) {
            if (!valid(row, mid, mode))
                continue;

            vector<int> dist(states, INF);
            queue<tuple<int,int,int>> q;

            dist[indexOf(row, mid, mode, l)] = 0;
            q.push({row, mid, mode});

            while (!q.empty()) {
                auto [x, y, m] = q.front();
                q.pop();

                int current = dist[indexOf(x, y, m, l)];

                for (int d = 0; d < 4; d++) {
                    int nx = x + dr[d];
                    int ny = y + dc[d];

                    if (ny < l || ny > r)
                        continue;

                    if (!valid(nx, ny, m))
                        continue;

                    int pos = indexOf(nx, ny, m, l);

                    if (dist[pos] == INF) {
                        dist[pos] = current + 1;
                        q.push({nx, ny, m});
                    }
                }

                if (grid[x][y] == '.') {
                    int nm = 1 - m;
                    int pos = indexOf(x, y, nm, l);

                    if (dist[pos] == INF) {
                        dist[pos] = current + 1;
                        q.push({x, y, nm});
                    }
                }
            }

            nodes[id].dist.push_back(move(dist));
        }
    }

    if (l < mid) {
        int child = build(l, mid - 1);
        nodes[id].left = child;
    }

    if (mid < r) {
        int child = build(mid + 1, r);
        nodes[id].right = child;
    }

    return id;
}

int query(int id, int sr, int sc, int er, int ec) {
    int answer = INF;

    while (id != -1) {
        const Node &node = nodes[id];

        int l = node.l;
        int mid = node.mid;

        int start = indexOf(sr, sc, 0, l);
        int endBlue = indexOf(er, ec, 0, l);
        int endRed = indexOf(er, ec, 1, l);

        for (const auto &dist : node.dist) {
            if (dist[start] == INF)
                continue;

            int endDist = min(dist[endBlue], dist[endRed]);

            if (endDist != INF) {
                answer = min(answer,
                             dist[start] + endDist);
            }
        }

        if (sc == mid || ec == mid)
            break;

        if (sc < mid && ec < mid) {
            id = node.left;
        }
        else if (sc > mid && ec > mid) {
            id = node.right;
        }
        else {
            break;
        }
    }

    return answer;
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

        for (int i = 0; i < N; i++)
            cin >> grid[i];

        nodes.clear();
        nodes.reserve(2 * M + 5);

        int root = build(0, M - 1);

        while (Q--) {
            int sr, sc, er, ec;
            long long K;

            cin >> sr >> sc >> er >> ec >> K;

            int shortest = query(root, sr, sc, er, ec);

            cout << (shortest <= K ? "YES" : "NO") << '\n';
        }
    }
}
