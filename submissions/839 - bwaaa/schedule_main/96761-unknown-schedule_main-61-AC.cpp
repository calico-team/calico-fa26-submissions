#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve(){
    int n, m, k, p, rem = 0, ans = 0;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<=n; i++){
        cin >> p;
        adj[p].push_back(i);
    }
    vector<int> dep(n+1), cnt(m+1);
    function<void(int)> dfs = [&](int r){
        for(int ch : adj[r]){
            dep[ch] = dep[r]+1;
            if(dep[ch] <= m) cnt[dep[ch]]++;
            dfs(ch);
        }
    };
    dfs(0);
    for(int i=1; i<=m; i++){
        rem += cnt[i];
        ans += min(rem, k);
        rem = max(0LL, rem - k);
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) solve();
}