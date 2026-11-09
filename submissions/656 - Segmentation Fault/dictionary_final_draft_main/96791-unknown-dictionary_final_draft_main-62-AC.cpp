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

int dep[N],par[N],sub[N];
bool vis[N];
int a[N],deg[N],q[N],x[N],rt[N]/*,R[N],C[N]*/;
int ch[62*N][2],tot;

int ins(int o,int y){
    int r=++tot,u = r;
    FORR(b,0,30){
        int c = y>>b&1;
        ch[u][!c]=ch[o][!c],ch[u][c]=++tot;
        u=tot; o = ch[o][c];
    }
    return r;
} 

int ask(int u, int y){
    int res = 0;
    FORR(b,0,30){
        int c = y>>b&1;
        if(ch[u][!c]) u=ch[u][!c],res|=1<<b;
        else u = ch[u][c];
    }
    return res;
}

void solve(){
    int n;cin >> n;
    FOR(i,1,n+1) deg[i]=0;
    FOR(i,1,n+1) cin >> par[i],deg[par[i]]++;
    FOR(i,1,n+1) cin >> a[i];

    int e = 0;tot=0;
    FOR(i,1,n+1) if(!deg[i]) q[e++] = i;
    FOR(i,0,e) if(!--deg[par[q[i]]]){
        q[e++]=par[q[i]];
    }

    FOR(i,1,n+1) if(deg[i]){
        int c = 0, r=0, v = i;
        // 2 laps => all prefix xors in r
        for(; deg[v] < 3; v = par[v]){
            deg[v]++,x[v]=c;
            r = ins(r,c);
            c ^= a[v];
        }
        for(; deg[v]; v=par[v]) deg[v] = 0,rt[v]=r;
    }

    FORR(i,0,e){
        int v = q[i], p = par[v];
        x[v]=a[v]^x[p];
        rt[v] = ins(rt[p], x[v]);
    }


    FOR(i,1,n+1) cout << ask(rt[i],x[i])<<" \n"[i==n];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) solve();
}
