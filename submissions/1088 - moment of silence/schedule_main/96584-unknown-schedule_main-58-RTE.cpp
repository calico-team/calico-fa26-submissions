#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
vector <int> adj[10005];
int d[10005];

void dfs(int x, int dep) {
    d[x] = dep;
    for (auto i : adj[x]) dfs(i, dep + 1);
}
int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int tc; cin >> tc;
    while (tc--) {
        int n, m, k; cin >> n >> m >> k;
        int p[n + 1];
        for (int i = 0; i <= n; i++ )adj[i].clear();
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            adj[p[i]].push_back(i);
        }
        dfs(0, 0);
        int cnt[n + 1] = {0};
        for (int i = 1; i <= n; i++) cnt[d[i]]++;
        int ans = 0;
        int sm = 0;
        for (int i = 1; i <= m; i++) {
            sm += cnt[i];
            ans += min(sm, k);
            sm -= min(sm, k);
        }
        cout << ans << '\n';
    }
}