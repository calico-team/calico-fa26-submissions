#include <bits/stdc++.h>
using namespace std;
int xdirs[] = {0, -1, 0, 1};
int ydirs[] = {1, 0, -1, 0};
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];
    vector<vector<int>> group(n, vector<int>(m, -1));
    int cg = 0;
    for (int si = 0; si < n; si++) for (int sj = 0; sj < m; sj++) {
        if (group[si][sj] != -1) continue;
        deque<pair<int, int>> stack;
        stack.push_back({si, sj});
        group[si][sj] = cg;
        while (!stack.empty()) {
            auto [i, j] = stack.front();
            stack.pop_front();
            for (int dir = 0; dir < 4; dir++) {
                int ni = i+xdirs[dir];
                int nj = j+ydirs[dir];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                    if (grid[i][j] == grid[ni][nj] || grid[i][j] == '.' || grid[ni][nj] == '.') if (group[ni][nj] == -1) {
                        group[ni][nj] = cg;
                        stack.push_back({ni, nj});
                    }
                }
            }
        }
        cg++;
    }
    int si, sj, ei, ej;
    while (q--) {
        cin >> si >> sj >> ei >> ej;
        if (group[si][sj] == group[ei][ej]) cout << "YES\n";
        else cout << "NO\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tcs;
    cin >> tcs;
    while (tcs--) solve();
    cout.flush();
}   