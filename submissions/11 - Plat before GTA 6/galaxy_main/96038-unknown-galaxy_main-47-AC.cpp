#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

int dx[4]{-1, 0, 0, 1}, dy[4]{0, -1, 1, 0};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 0 = blue
    // 1 = red
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(m, vector<bool>(2)));
    if (a[n - 1][m - 1] != 'R') dp[n - 1][m - 1][0] = 1;
    if (a[n - 1][m - 1] != 'B') dp[n - 1][m - 1][1] = 1;

    queue<vector<int>> que;
    if (a[n - 1][m - 1] != 'R') que.push({n - 1, m - 1, 0});
    if (a[n - 1][m - 1] != 'B') que.push({n - 1, m - 1, 1});
    while (!que.empty()) {
        vector<int> v = que.front();
        que.pop();

        int x = v[0], y = v[1], t = v[2];
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                if (a[nx][ny] == 'B') {
                    if (t == 0 && !dp[nx][ny][t]) {
                        dp[nx][ny][t] = 1;
                        que.push({nx, ny, t});
                    }
                } else if (a[nx][ny] == 'R') {
                    if (t == 1 && !dp[nx][ny][t]) {
                        dp[nx][ny][t] = 1;
                        que.push({nx, ny, t});
                    }
                } else {
                    if (!dp[nx][ny][0]) {
                        dp[nx][ny][0] = 1;
                        que.push({nx, ny, 0});
                    }
                    if (!dp[nx][ny][1]) {
                        dp[nx][ny][1] = 1;
                        que.push({nx, ny, 1});
                    }
                }
            }
        }
    }

    while (q--) {
        int x, y, tmp1, tmp2;
        cin >> x >> y >> tmp1 >> tmp2;

        cout << ((dp[x][y][0] || dp[x][y][1]) ? "YES" : "NO") << endl;
    }
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve();
    }

    return 0;
}