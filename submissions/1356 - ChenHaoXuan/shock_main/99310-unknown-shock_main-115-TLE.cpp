#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
#define MAXN 1005

int ans = 0; 
int maxn = 0;

ll isqrt(ll x) {
    if (x < 0) return 0;
    ll r = sqrt(x);
    while (r * r > x) r--;
    while ((r + 1) * (r + 1) <= x) r++;
    return r;
}

struct DSU {
    //stack<array<int, 4>>stk;
    int link[MAXN], sz[MAXN];
    void init(int n) {
        for (int i = 1; i <= n; i++) { link[i] = i; sz[i] = 1; }
    }
    int find(int x) {
        while (x != link[x]) x = link[x];
        return x;
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        link[b] = a;
        --ans; maxn = max(maxn, sz[a]);
    }
};
DSU dsu[MAXN];

void solve()
{
    int n,m,q; cin>>n>>m>>q;
    vector<pair<pair<ll, ll>, ll>>v(q);
    for(int i=0;i<q;i++)cin>>v[i].first.first>>v[i].first.second>>v[i].second;
    for(int i=0;i<n;i++)dsu[i].init(m+1);
    vector<vector<ll>>ans(n, vector<ll>(m, 0));
    for(int i=q-1;i>=0;i--){
        for(ll j = max(0LL,v[i].first.first-v[i].second);j<=min((ll)n-1, v[i].first.first+v[i].second);j++){
            if(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first) >= 0){
                if(max(0LL, v[i].first.second-isqrt(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first))) > min((ll)m-1, v[i].first.second+isqrt(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first))))continue;
                int cc = dsu[j].find(max(0LL, v[i].first.second-isqrt(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first))) + 1);
                while(cc <= min((ll)m-1, v[i].first.second+isqrt(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first))) + 1){
                    ans[j][cc-1] = v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first) - (cc-1-v[i].first.second) *(cc-1-v[i].first.second) + 1;
                    dsu[j].link[cc] = dsu[j].find(cc + 1);
                    cc = dsu[j].find(cc);
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<ans[i][j]<<(j == m-1 ? "" : " ");
        }
        cout<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}