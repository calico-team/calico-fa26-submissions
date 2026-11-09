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
const int N=1e6+5;

int dep[N],par[N],sub[N];
bool vis[N];
int a[N],x[N],y[N],p[N];

int f(int v){
    while(par[v] != v) v = par[v] = par[par[v]];
    return v;
}

void solve(){
    int n, m, q; cin >> n >> m >> q;
    FOR(i,0,q) cin >> x[i] >> y[i] >> p[i];
    FOR(i,0,n*m+1) par[i] = i, a[i] = 0;

   
    FORR(k,0,q){
        FOR(r, x[k]-p[k], x[k]+p[k]+1){
            int d = p[k]*p[k]-(r-x[k])*(r-x[k]), h = sqrt(d);
            int e = r*m+y[k]+h;
            for(int j = f(e-2*h); j <= e; j = f(j)){
                int c = j-r*m-y[k];
                a[j] = d-c*c+1;
                par[j]=j+1;
            }
        }
    }

    FOR(i,0,n*m) cout << a[i] << " \n"[(i+1)%m == 0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) solve();
}
