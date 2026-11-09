#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define bk back()
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+5;

vector<int> adj[N];
vector<pii> g[N];
int dep[N],par[N],sub[N];
bool vis[N];
int q[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; int n; cin >> s >> n;
    int x = 0, p = 0;
    if(s[0] == 'S'){
        FOR(i,1,n+1){
            cin >> par[i];
            if(par[i] < 0) p=i;
            else x ^= par[i];
        }
        par[p] = x;
        FOR(i,2,n+1) cout << i << ' ' << par[i] << '\n';
        return 0;
    }

    FOR(i,1,n){
        int u, v;cin >> u >> v;
        adj[u].pb(v); adj[v].pb(u);
    }

    // xor(par)=0
    int m = 1; q[0]=1;
    FOR(i,0,n){
        int v = q[i];
        for(int w : adj[v]) if(w != par[v]){
            par[w ]=v,x^=v; q[m++] = w;
        }
    }
    par[1] = x;

    FOR(i,1,n+1) cout << par[i]<<' '; cout << '\n';
}
