#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")

#define ll long long
#define f first
#define s second
#define inf (1LL << 60)

bool v[12][4002][2];
ll dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
ll T, R, C, Q, d[12][4002][2], ans[100001];
char g[12][4002];
vector<pair<pair<ll, ll>, pair<pair<ll, ll>, pair<ll, ll>>>> ql;

void bfs(pair<ll, ll> s) {
    queue<pair<ll, pair<ll, ll>>> q;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            v[i][j][0] = 0;
            v[i][j][1] = 0;
            d[i][j][0] = inf;
            d[i][j][1] = inf;
        }
    }
    v[s.f][s.s][0] = 1;
    d[s.f][s.s][0] = 0;
    q.push({0, s});
    while (q.size()) {
        pair<ll, pair<ll, ll>> cur = q.front();
        q.pop();
        if (g[cur.s.f][cur.s.s] == '.' && !v[cur.s.f][cur.s.s][1 - cur.f]) {
            v[cur.s.f][cur.s.s][1 - cur.f] = 1;
            d[cur.s.f][cur.s.s][1 - cur.f] = d[cur.s.f][cur.s.s][cur.f] + 1;
            q.push({1 - cur.f, cur.s});
        }
        for (int i = 0; i < 4; i++) {
            ll nr = cur.s.f + dr[i], nc = cur.s.s + dc[i];
            if (1 <= nr && nr <= R && 1 <= nc && nc <= C && !v[nr][nc][cur.f]) {
                if (g[nr][nc] == '.' || (cur.f == 0 && g[nr][nc] == 'B') || (cur.f == 1 && g[nr][nc] == 'R')) {
                    v[nr][nc][cur.f] = 1;
                    d[nr][nc][cur.f] = d[cur.s.f][cur.s.s][cur.f] + 1;
                    q.push({cur.f, {nr, nc}});
                }
            }
        }
    }
}

void solve() {
    cin >> R >> C >> Q;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> g[i][j];
        }
    }
    ql.clear();
    for (int i = 0; i < Q; i++) {
        ll r1, c1, r2, c2, k;
        cin >> r1 >> c1 >> r2 >> c2 >> k;
        ql.push_back({{r1 + 1, c1 + 1}, {{r2 + 1, c2 + 1}, {k, i}}});
    }
    sort(ql.begin(), ql.end());
    for (int i = 0; i < Q; i++) {
        if (i == 0 || ql[i].f != ql[i - 1].f) {
            bfs(ql[i].f);
        }
        if (g[ql[i].s.f.f][ql[i].s.f.s] == 'B') {
            ans[ql[i].s.s.s] = (d[ql[i].s.f.f][ql[i].s.f.s][0] <= ql[i].s.s.f);
        }
        else if (g[ql[i].s.f.f][ql[i].s.f.s] == 'R') {
            ans[ql[i].s.s.s] = (d[ql[i].s.f.f][ql[i].s.f.s][1] <= ql[i].s.s.f);
        }
        else {
            ans[ql[i].s.s.s] = (min(d[ql[i].s.f.f][ql[i].s.f.s][0], d[ql[i].s.f.f][ql[i].s.f.s][1]) <= ql[i].s.s.f);
        }
    }
    for (int i = 0; i < Q; i++) {
        if (ans[i]) {
            cout << "YES" << '\n';
        }
        else {
            cout << "NO" << '\n';
        }
    }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}