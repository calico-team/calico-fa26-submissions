#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> g(n);
        for (auto &s : g) cin >> s;
        vector<int> p(2 * n * m);
        iota(p.begin(), p.end(), 0);
        function<int(int)> f = [&](int x){return p[x] == x ? x : p[x] = f(p[x]);};
        auto id = [&](int k, int i, int j){return k * n * m + i * m + j; };
        auto on = [&](int k, int i, int j){ return g[i][j] == '.' || g[i][j] == (k ? 'R' : 'B');};
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++){
                    if (!on(k, i, j)) continue;
                    if (g[i][j] == '.' && k == 0) p[f(id(0, i, j))] = f(id(1, i, j));
                    if (i + 1 < n && on(k, i + 1, j)) p[f(id(k, i, j))] = f(id(k, i + 1, j));
                    if (j + 1 < m && on(k, i, j + 1)) p[f(id(k, i, j))] = f(id(k, i, j + 1));}
        while (q--){
            int a, b, c, e;
            cin >> a >> b >> c >> e;
            int k = g[c][e] == 'R';
            cout << (f(id(0, a, b)) == f(id(k, c, e)) ? "YES" : "NO") << "\n";}}}