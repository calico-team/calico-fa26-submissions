#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

struct Query {
    int r1, c1, r2, c2, k, id;
};

int n, m, q;
char grid[12][4005];
bool answer[100005];
int distbuf[20][11][4005][2];
int qr[80005], qc[80005], qm[80005];

bool active(char ch, int mode) {
    return ch == '.' || (mode == 0 && ch == 'B') || (mode == 1 && ch == 'R');
}

void solve(int l, int r, const vector<Query>& queries) {
    if (l > r || queries.empty()) return;

    int mid = (l + r) / 2;
    int count = 0;
    int rows[20], modes[20];

    for (int i = 0; i < n; ++i) {
        for (int z = 0; z < 2; ++z) {
            if (active(grid[i][mid], z)) {
                rows[count] = i;
                modes[count] = z;
                ++count;
            }
        }
    }

    static constexpr int dr[4] = {-1, 1, 0, 0};
    static constexpr int dc[4] = {0, 0, -1, 1};

    for (int s = 0; s < count; ++s) {
        for (int i = 0; i < n; ++i) {
            for (int j = l; j <= r; ++j) {
                distbuf[s][i][j][0] = INF;
                distbuf[s][i][j][1] = INF;
            }
        }

        int head = 0, tail = 0;
        int sr = rows[s], mode = modes[s];

        distbuf[s][sr][mid][mode] = 0;
        qr[tail] = sr;
        qc[tail] = mid;
        qm[tail] = mode;
        ++tail;

        while (head < tail) {
            int x = qr[head], y = qc[head], z = qm[head];
            ++head;
            int d = distbuf[s][x][y][z] + 1;

            if (grid[x][y] == '.' && distbuf[s][x][y][z ^ 1] == INF) {
                distbuf[s][x][y][z ^ 1] = d;
                qr[tail] = x;
                qc[tail] = y;
                qm[tail] = z ^ 1;
                ++tail;
            }

            for (int j = 0; j < 4; ++j) {
                int xx = x + dr[j], yy = y + dc[j];

                if (xx < 0 || xx >= n || yy < l || yy > r) continue;

                if (!active(grid[xx][yy], z) || distbuf[s][xx][yy][z] != INF) continue;

                distbuf[s][xx][yy][z] = d;
                qr[tail] = xx;
                qc[tail] = yy;
                qm[tail] = z;
                ++tail;
            }
        }
    }

    vector<Query> left, right;

    for (const auto &x : queries) {
        bool ok = false;

        for (int s = 0; s < count && !ok; ++s) {
            int d1 = distbuf[s][x.r1][x.c1][0];
            if (d1 > x.k) continue;

            int d2 = min(distbuf[s][x.r2][x.c2][0], distbuf[s][x.r2][x.c2][1]);

            if (d2 != INF && d1 + d2 <= x.k) ok = true;
        }

        if (ok) {
            answer[x.id] = true;
        } else if (x.c1 < mid && x.c2 < mid) {
            left.push_back(x);
        } else if (x.c1 > mid && x.c2 > mid) {
            right.push_back(x);
        }
    }

    solve(l, mid - 1, left);
    solve(mid + 1, r, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m >> q;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < m; ++j) grid[i][j] = s[j];
        }

        vector<Query> queries(q);

        for (int i = 0; i < q; ++i) {
            cin >> queries[i].r1 >> queries[i].c1 >> queries[i].r2 >> queries[i].c2 >> queries[i].k;
            queries[i].id = i;
        }

        fill(answer, answer + q, false);
        solve(0, m - 1, queries);

        for (int i = 0; i < q; ++i) cout << (answer[i] ? "YES" : "NO") << '\n';
    }

    return 0;
}
