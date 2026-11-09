#include <bits/stdc++.h>
using namespace std;
#define int long long
template<class T> inline void setmax(T& a, T b) {if (a < b) a = b;}
template<class T> inline void setmin(T& a, T b) {if (a > b) a = b;}
struct state {
    int x, y;
    bool m;
};
signed main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        queue<state> p;
        vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(2, 0)));
        p.push({x2, y2, 0});
        while (!p.empty()) {
            state s = p.front();
            p.pop();
            if (s.x >= n || s.x < 0 || s.y >= m || s.y < 0) continue;
            if ((v[s.x][s.y] == 'R' and s.m == 0) or (v[s.x][s.y] == 'B' and s.m == 1)) continue;
            if (vis[s.x][s.y][s.m]) continue;
            vis[s.x][s.y][s.m] = 1;
            p.push({s.x + 1, s.y, s.m});
            p.push({s.x - 1, s.y, s.m});
            p.push({s.x, s.y + 1, s.m});
            p.push({s.x, s.y - 1, s.m});
            p.push({s.x, s.y, !s.m});
        }
        if (vis[x1][y1][0]) cout << "YES" << endl;
        else cout << "NO" << endl;
        q--;
        while (q > 0) {
            cin >> x1 >> y1 >> x2 >> y2;
            if (vis[x1][y1][0]) cout << "YES" << endl;
            else cout << "NO" << endl;
            q--;
        }
    }
}