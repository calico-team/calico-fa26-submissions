#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using lli=long long int;
using pii=pair<int, int>;
using plli=pair<lli, lli>;
using vlli=vector<lli>;
using vpii=vector<pii>;
using vplli=vector<plli>;
using vvi=vector<vi>;
using vvlli=vector<vlli>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vector<bool>>;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--){
        int n, m, k;
        cin >> n >> m >> k;
        vi par(n);
        for (int i=0; i<n; ++i) cin >> par[i], --par[i];
        vvi G(n);
        vi dist(n, 1e9);
        queue<int> q;
        for (int i=0; i<n; ++i){
            if (par[i]==-1) q.push(i), dist[i]=0;
            else G[par[i]].push_back(i);
        }
        while (!q.empty()){
            int u=q.front();
            q.pop();
            for (int v : G[u]){
                dist[v]=dist[u]+1;
                q.push(v);
            }
        }
        vi cnt(n+1, 0);
        for (int i=0; i<n; ++i) ++cnt[dist[i]];
        int ans=0;
        int s=0;
        for (int i=0; i<m; ++i){
            if (i<=n) s+=cnt[i];
            ans+=min(s, k);
            s-=min(s, k);
        }
        cout << ans << endl;
    }
}