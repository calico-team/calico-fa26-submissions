#include <bits/stdc++.h>
using namespace std;

// #pragma GCC optimize("O3,unroll-loops")

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvl;
typedef pair<ll, ll> pll;
typedef long double ld;

#define sp << " " <<
#define sz(x) (ll)(x.size())
#define debug(x) cout << x << endl

const ll BIG=1e18;
const ll MOD=1e9+7;
const ll INF=1e9;
const ll MOD1=998244353;
const ll MX=1e6+5;

ll x4[4]={-1, 1, 0, 0};
ll y4[4]={0, 0, -1, 1};

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vll par(n), dep(n, -1); // depth >m can be ignored
    vvl adj(n);
    for (ll i=0; i<n; i++) {
        cin >> par[i];
        par[i]--;
        if (par[i]==-1) dep[i]=0;
        else adj[par[i]].push_back(i);
    }
    auto dfs=[&](auto&& self, ll u, ll p) -> void {
        if (p!=-1) dep[u]=dep[p]+1;
        for (auto v:adj[u]) {
            if (v==p) continue;
            self(self, v, u);
        }
    };
    for (ll i=0; i<n; i++) {
        if (par[i]==-1) {
            dfs(dfs, i, -1);
        }
    }
    vll freq(n, 0);
    for (ll i=0; i<n; i++) freq[dep[i]]++;
    // for (ll i=0; i<n; i++) cout << dep[i] << " ";
    // cout << endl;
    vll suff(n, 0);
    suff[n-1]=freq[n-1];
    for (ll i=(n-2); i>=0; i--) suff[i]=suff[i+1]+freq[i];
    ll mx=0;
    for (ll i=0; i<n; i++) {
        // debug(i sp suff[i] sp k sp m-i+1);
        ll te=k*(m-i);
        if (i>(m-1)) te=0;
        mx=max(mx, suff[i]-te);
    }
    cout << n-mx << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll tc=1;
    cin >> tc;
    while (tc--) solve();
}