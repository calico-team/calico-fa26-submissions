#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vll vector<ll>
#define vvl vector<vll>
#define pll pair<ll,ll>
#define bismillah ios_base::sync_with_stdio(false); 
#define medal cin.tie(NULL);
const ll INF = 4e18;
#define pb push_back
#define fi first
#define se second
#define vpll vector<pll>
const ll mod = 1e9 + 7;
const ll maxn = 1e4 + 7;
#define eb emplace_back
const ll maxlog = 20;
vll ADJ[maxn];
ll vis[maxn];
ll dp[maxn];

ll n,m,k;



void dfs(ll node, ll prv){
if(node != 0)vis[node] = vis[prv] + 1;

vll v;
dp[node] = 1;
if(vis[node] == m) return;

for(auto next : ADJ[node]){
    if(next == prv) continue;
    dfs(next,node);
    v.pb(dp[next]);
}

sort(v.begin(),v.end(),greater<ll>());
for(ll i = 0; i < min((ll)v.size(),k); i++) dp[node] += v[i];
}




void solve(){
    cin >> n >> m >> k;
    vis[0] = 0;
    memset(dp,0,sizeof(dp));
    memset(vis,0,sizeof(vis));
    for(ll i = 0; i <= n; i++) ADJ[i].clear();

    for(ll i = 1; i <= n; i++){
        ll u; cin >> u;
        ADJ[i].pb(u);
        ADJ[u].pb(i);
    }

    dfs(0,-1);
    //for(ll i = 0; i <= n; i++) cout << dp[i] << " ";
    cout << dp[0] - 1 << '\n';



}


int main(){
    bismillah medal
    ll t; cin >> t;
    while(t--)solve();
}