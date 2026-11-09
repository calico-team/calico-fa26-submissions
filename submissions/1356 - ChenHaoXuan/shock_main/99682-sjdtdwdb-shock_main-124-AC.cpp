#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;

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
    vector<int> link, sz;
    void init(int n) {
        link.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) { link[i] = i; }
    }
    int find(int x) {
        if (x == link[x]) return x;
        return link[x] = find(link[x]); 
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

void solve()
{
    int n,m,q; cin>>n>>m>>q;
    vector<pair<pair<ll, ll>, ll>>v(q);
    for(int i=0;i<q;i++)cin>>v[i].first.first>>v[i].first.second>>v[i].second;
    vector<DSU>dsu(n);
    for(int i=0;i<n;i++)dsu[i].init(m+1);
    vector<vector<ll>>ans(n, vector<ll>(m, 0));
    for(int i=q-1;i>=0;i--){
        for(ll j = max(0LL,v[i].first.first-v[i].second);j<=min((ll)n-1, v[i].first.first+v[i].second);j++){
            if(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first) >= 0){
                ll d = isqrt(v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first));
                if(max(0LL, v[i].first.second-d) > min((ll)m-1, v[i].first.second+d))continue;
                int cc = dsu[j].find(max(0LL, v[i].first.second-d) + 1);
                while(cc <= min((ll)m-1, v[i].first.second+d) + 1){
                    ans[j][cc-1] = v[i].second *v[i].second- (j-v[i].first.first) *(j-v[i].first.first) - (cc-1-v[i].first.second) *(cc-1-v[i].first.second) + 1;
                    dsu[j].link[cc] = dsu[j].find(cc + 1);
                    cc = dsu[j].find(cc);
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<ans[i][j]<<" ";
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