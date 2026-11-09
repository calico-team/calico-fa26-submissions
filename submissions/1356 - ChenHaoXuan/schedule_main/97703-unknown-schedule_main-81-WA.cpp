#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
const int MAXN = 10005;
vector<int>adj[MAXN];
bool vis[MAXN];
int h[MAXN];
vector<int>ans;
 
void dfs(int s) {
	vis[s] = true;
	for (auto u : adj[s]) {
		if (!vis[u])dfs(u);
	}
	ans.push_back(s);
}
 
void compute(int n){
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i);
		}
	}
	reverse(ans.begin(), ans.end());
}

void solve()
{
    int n,m,k; cin>>n>>m>>k;
    for(int i =0;i<=n;i++){
        adj[i].clear();
        vis[i] = false;h[i] = 1;
    }
    ans.clear();
    vector<int>v(n + 1);
    for(int i =1;i<=n;i++){
        cin>>v[i];
        if(v[i]!=0)adj[v[i]].push_back(i);
    }
    compute(n);
    for(int i = n-1;i>=0;i--){
        for(auto u : adj[ans[i]])h[u] = max(h[ans[i]], h[u]+1);
    }
    priority_queue<pair<int, int>>pq;
    for(int i = 1; i <= n; i++) {
        if(v[i] == 0) {
            pq.push({h[i], i});
        }
    }
    int ans = 0;
    for(int i =1;i<=m;i++){
        int cnt = 0;
        vector<int>a;
        while(pq.size()&&cnt<k){
            int u = pq.top().second;
            pq.pop();
            ++cnt; ++ans;
            for(auto v : adj[u])a.push_back(v);
        }
        for(auto u : a)pq.push({h[u], u});
    }
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}