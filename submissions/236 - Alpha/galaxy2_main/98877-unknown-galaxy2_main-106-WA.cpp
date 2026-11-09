#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        const int INF = 1e9;
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> g(n);
        for (auto &s : g) cin >> s;
        vector<array<int, 5>> e(q);
        for (auto &x : e) cin >> x[0] >> x[1] >> x[2] >> x[3] >> x[4];
        vector<int> best(q, INF);
        auto on = [&](int r, int c, int k){ return g[r][c] == '.' || g[r][c] == (k ? 'R' : 'B');};
        function<void(int, int, vector<int>&)> go = [&](int l, int r, vector<int> &ids){
            if (ids.empty()) return;
            int mid = (l + r) / 2, w = r - l + 1, S = 2 * n * w;
            auto id = [&](int rr, int c, int k){ return ((c - l) * n + rr) * 2 + k;};
            vector<int> D(2 * n * S, INF), qu(S);
            for (int s = 0; s < 2 * n; s++){
                int row = s / 2, k = s % 2;
                if (!on(row, mid, k)) continue;
                int *d = &D[s * S]; int h = 0, tt = 0;
                d[id(row, mid, k)] = 0; qu[tt++] = id(row, mid, k);
                while (h < tt){
                    int u = qu[h++];
                    int kk = u & 1, rr = (u >> 1) % n, c = (u >> 1) / n + l;
                    auto push = [&](int r2, int c2, int k2){
                        if (r2 < 0 || r2 >= n || c2 < l || c2 > r || !on(r2, c2, k2)) return;
                        int v = id(r2, c2, k2);
                        if (d[v] == INF){
                            d[v] = d[u] + 1; qu[tt++] = v;}
                    };
                    push(rr + 1, c, kk); push(rr - 1, c, kk);
                    push(rr, c + 1, kk); push(rr, c - 1, kk);
                    if (g[rr][c] == '.') push(rr, c, 1 - kk);}}
            for (int i : ids){
                int si = id(e[i][0], e[i][1], 0);
                for (int s = 0; s < 2 * n; s++){
                    int ds = D[s * S + si];
                    if (ds >= INF) continue;
                    for (int k = 0; k < 2; k++){
                        int di = D[s * S + id(e[i][2], e[i][3], k)];
                        if (di < INF) best[i] = min(best[i], ds + di);}}}
            if (l == r) return;
            vector<int> a, b;
            for (int i : ids){
                int lo = min(e[i][1], e[i][3]), hi = max(e[i][1], e[i][3]);
                if (hi <= mid) a.push_back(i);
                else if (lo > mid) b.push_back(i);}
            go(l, mid, a);
            go(mid + 1, r, b); };
        vector<int> all(q);
        iota(all.begin(), all.end(), 0);
        go(0, m - 1, all);
        for (int i = 0; i < q; i++) cout << (best[i] <= e[i][4] ? "YES" : "NO") << "\n";}}