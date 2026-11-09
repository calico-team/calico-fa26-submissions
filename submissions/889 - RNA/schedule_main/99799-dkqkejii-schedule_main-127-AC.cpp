#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
const int maxn=1e4+7;
int n,m,k,ans=0;
vector<vector<int>> a;
vector<int> son_number;
void dfs(int u) {
    son_number[u]=1;
    for(int v:a[u]) {
        dfs(v);
        son_number[u]+=son_number[v];
    }
}
signed main() {
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T;cin>>T;
    while(T--) {
        cin>>n>>m>>k;
        a.assign(n+1,{});
        son_number.assign(n+1,0);
        for(int i=1;i<=n;i++) {
            int x;cin>>x;
            a[x].push_back(i);
        }
        dfs(0);
        priority_queue<pair<int,int>> pq;
        for(int v:a[0])
            pq.push({son_number[v],v});
        for(int i=1;i<=m&&!pq.empty();i++) {
            vector<int>next;
            for(int j=1;j<=k&&!pq.empty();j++) {
                int u=pq.top().second;pq.pop();
                ans++;
                for(int v:a[u])
                    next.push_back(v);
            }
            for(int v:next)
                pq.push({son_number[v],v});
        }
        cout<<ans<<endl;
        ans=0;
    }
    return 0;
}