#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;
vector<vector<int>> ch(N);
vector<int> h(N);

void dfs(int node) {
    h[node] = 1;
    for (int v : ch[node]) {
        dfs(v);
        h[node] = max(h[node], h[v] + 1);
    }
}
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> P;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        if (p == 0) P.push_back(i);
        else ch[p].push_back(i);
    }
    for (int u : P) dfs(u);
    priority_queue<pair<int, int>> pq;
    for (int u : P) pq.push({h[u], u});
    int ans = 0;
    while(m--){
        vector<int> cur;
        for (int j = 0; j < k && !pq.empty(); j++) {
            int u = pq.top().second;
            pq.pop();
            cur.push_back(u);
        }
        ans += cur.size();
        for (int u : cur) for (int v : ch[u]) pq.push({h[v], v});
        if (pq.empty()) break;
    }
    cout << ans << '\n';
    for(int i = 1 ; i <= n ; i ++)ch[i].clear(),h[i]=0;
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
