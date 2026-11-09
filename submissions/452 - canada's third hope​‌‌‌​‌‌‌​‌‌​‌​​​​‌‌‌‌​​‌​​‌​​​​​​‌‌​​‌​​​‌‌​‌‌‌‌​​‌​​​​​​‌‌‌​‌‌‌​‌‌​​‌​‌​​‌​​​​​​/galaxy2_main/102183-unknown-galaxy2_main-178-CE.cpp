#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define ll long long
#define f first
#define s second
#define inf (1LL << 60)

struct state {
    ll f, colour, r, c;
    bool operator>(const state& other) const {
        return f > other.f;
    }
};

struct query {
    ll r1, c1, r2, c2, k, id;
};

bool v[12][4002][2];
ll dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
ll T, R, C, Q, d[12][4002][2], ans[100001];
char g[12][4002];
vector<query> ql;

ll heuristic(ll r1, ll c1, ll r2, ll c2) {
    return abs(r1 - r2) + abs(c1 - c2);
}

void astar(pair<ll, ll> s, pair<int, int> e) {
    priority_queue<state, vector<state>, greater<state>> pq;
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
    ll starth = heuristic(s.f, s.s, e.f, e.s);
    pq.push({starth, 0, s.f, s.s});
    while (pq.size()) {
        state cur = pq.top();
        pq.pop();
        if (cur.r == e.f && cur.c == e.s) return;
        if (g[cur.r][cur.c] == '.' && !v[cur.r][cur.c][1 - cur.colour]) {
            v[cur.r][cur.c][1 - cur.colour] = 1;
            d[cur.r][cur.c][1 - cur.colour] = d[cur.r][cur.c][cur.colour] + 1;

            ll h = heuristic(cur.r, cur.c, e.f, e.s);
            ll f = d[cur.r][cur.c][1 - cur.colour] + h;
            pq.push({f, 1 - cur.colour, cur.r, cur.c});
        }
        for (int i = 0; i < 4; i++) {
            ll nr = cur.r + dr[i], nc = cur.c + dc[i];
            if (1 <= nr && nr <= R && 1 <= nc && nc <= C && !v[nr][nc][cur.colour]) {
                if (g[nr][nc] == '.' || (cur.colour == 0 && g[nr][nc] == 'B') || (cur.colour == 1 && g[nr][nc] == 'R')) {
                    v[nr][nc][cur.colour] = 1;
                    d[nr][nc][cur.colour] = d[cur.r][cur.c][cur.colour] + 1;

                    ll h = heuristic(nr, nc, e.f, e.s);
                    ll f = d[nr][nc][cur.colour] + h;
                    pq.push({f, cur.colour, nr, nc});
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
        ql.push_back({r1+1, c1+1, r2+1, c2+1, k, i});
    }
    
    for(int i = 0; i < Q; i++) {
        astar({ql[i].r1, ql[i].c1}, {ql[i].r2, ql[i].c2});
        if(g[ql[i].r2][ql[i].c2] == 'B') {
            ans[ql[i].id] = (d[ql[i].r2][ql[i].c2][0] <= ql[i].k);
        } else if(g[ql[i].r2][ql[i].c2] == 'R') {
            ans[ql[i].id] = (d[ql[i].r2][ql[i].c2][1] <= ql[i].k);
        } else {
            ans[ql[i].id] = (min(d[ql[i].r2][ql[i].c2][0], d[ql[i].r2][ql[i].c2][1]) <= ql[i].k);
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