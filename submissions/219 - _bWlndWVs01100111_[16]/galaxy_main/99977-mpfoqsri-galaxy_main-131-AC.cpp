#include <bits/stdc++.h>
#define debug(x) cout << #x << " is " << x << endl;
using namespace std;
#define int long long
#define pii pair<int, int>
template<typename T> using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using vv = vector<vector<T>>;
template<typename T> using v = vector<T>;
#define fb(x) x.begin(), x.end()
#define lsb(x) (x & -x)

v<pii> dir = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1},
};

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int tc; cin >> tc;

    while (tc--) {
        int n, m, q; cin >> n >> m >> q;

        vv<int> grid(n, v<int>(m));
        for (auto &row : grid) {
            for (int &cell : row) {
                char temp; cin >> temp;
                if (temp == 'R') cell = 1;
                else if (temp == 'B') cell = 0;
                else cell = -1;
            }
        }

        vv<v<int>> comp(n, vv<int>(m, v<int>(2, -1)));

        int cid = 0;

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                for (int s = 0; s < 2; s++) {

                    if (grid[r][c] != -1 && grid[r][c] != s) continue;

                    if (comp[r][c][s] != -1) continue;

                    queue<tuple<int, int, int>> rawr;
                    rawr.push({c, r, s});
                    comp[r][c][s] = cid;

                    while (!rawr.empty()) {
                        auto [x, y, state] = rawr.front();
                        rawr.pop();

                        for (auto [dx, dy] : dir) {
                            int nx = x + dx;
                            int ny = y + dy;

                            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

                            if (grid[ny][nx] != -1 && grid[ny][nx] != state) continue;
                            if (comp[ny][nx][state] != -1) continue;

                            comp[ny][nx][state] = cid;
                            rawr.push({nx, ny, state});
                        }

                        if (grid[y][x] == -1 && comp[y][x][1 - state] == -1) {
                            comp[y][x][1 - state] = cid;
                            rawr.push({x, y, 1 - state});
                        }
                    }

                    cid++;
                }
            }
        }

        while (q--) {
            int xs, ys, xe, ye;
            cin >> xs >> ys >> xe >> ye;

            int start = comp[xs][ys][0];

            if (start == comp[xe][ye][0] || start == comp[xe][ye][1]) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}
