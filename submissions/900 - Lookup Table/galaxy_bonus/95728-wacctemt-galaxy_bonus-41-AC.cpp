// SAY REX

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ul = unsigned long;
using ld = long double;

void dfs(vector<vector<ll>> &group, vector<vector<char>> &grid, ll r, ll c, ll x, ll n, ll m) {
    group[r][c] = x;
    char curr = grid[r][c];
    if (r > 0) {
        ll nxt = grid[r-1][c];
        if (group[r-1][c] == -1 && !(nxt != '.' && curr != '.' && nxt != curr)) {
            dfs(group, grid, r-1, c, x, n, m);
        }
    }
    if (r < n - 1) {
        ll nxt = grid[r+1][c];
        if (group[r+1][c] == -1 && !(nxt != '.' && curr != '.' && nxt != curr)) {
            dfs(group, grid, r+1, c, x, n, m);
        }
    }
    if (c > 0) {
        ll nxt = grid[r][c-1];
        if (group[r][c-1] == -1 && !(nxt != '.' && curr != '.' && nxt != curr)) {
            dfs(group, grid, r, c-1, x, n, m);
        }
    }
    if (c < m - 1) {
        ll nxt = grid[r][c+1];
        if (group[r][c+1] == -1 && !(nxt != '.' && curr != '.' && nxt != curr)) {
            dfs(group, grid, r, c+1, x, n, m);
        }
    }
}

void solve() {
    ll n, m, q;
    cin >> n >> m >> q;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<ll>> group(n, vector<ll>(m, -1));
    for (ll i = 0; i < n; ++i) {
        string x;
        cin >> x;
        for (ll j = 0; j < m; ++j) {
            grid[i][j] = x[j];
        }
    }

    ll num = 1;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < m; ++j) {
            if (group[i][j] == -1) {
                dfs(group, grid, i, j, num, n, m);
                num++;
            }
        }
    }

    for (ll i = 0; i < q; ++i) {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        if (group[r1][c1] == group[r2][c2]) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
}

signed main() {
	ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}
