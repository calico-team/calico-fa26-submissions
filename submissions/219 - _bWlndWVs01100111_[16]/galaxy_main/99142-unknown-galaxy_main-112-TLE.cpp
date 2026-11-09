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

        while (q--) {
            int xs, ys, xe, ye; cin >> ys >> xs >> ye >> xe;
            vv<v<bool>> visited(n, vv<bool>(m, v<bool>(2)));
            queue<tuple<int, int, int>> rawr;
            rawr.push({xs, ys, 0});
            while (!rawr.empty()) {
                auto [x, y, state] = rawr.front();
                rawr.pop();

                if (x < 0 || x >= m || y < 0 || y >= n) continue;
                if (visited[y][x][state]) continue;

                visited[y][x][state] = true;

                for (auto [cx, cy] : dir) {
                    int nx = x + cx;
                    int ny = y + cy;

                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;

                    if (grid[ny][nx] == -1 || grid[ny][nx] == state) {
                        rawr.push({nx, ny, state});
                    }
                }

                if (grid[y][x] == -1) {
                    rawr.push({x, y, 1 - state});
                }
            }
            if (visited[ye][xe][1] or visited[ye][xe][0]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}
