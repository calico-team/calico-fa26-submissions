#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())

using namespace std;

const ll MOD = 1e9 + 7;

// just keeping this here in case i need it later
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(a, b % a);
}
void fastio() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
ll pw(ll b, ll e) {
    ll r = 1;
    b %= MOD;
    if(b < 0) b += MOD;

    while(e) {
        if(e&1) r = r * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }

    return r;
}
void do_first() {
    int n ;
    cin >>n;

    vector<vector<int>> adj(n + 1);
    for(int i= 0; i < n - 1; i++) {
        int u, v;
        cin>> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    //just store parent for everyone
    vector<int> par(n + 1, 0);
    queue<int> q;
    q.push(1);
    par[1] = 1;

    int xr_sum = 0;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i =0; i< sz(adj[u]); i++) {
            int nxt = adj[u][i];
            if(par[nxt] == 0) {
                par[nxt] = u;
                xr_sum ^= u;
                q.push(nxt);
            }
        }
    }

    // a[1] holds the xor of all other parents so if 1 gets erased we still know a[2..n]
    // recovery also posible
    par[1] = xr_sum;

    for(int i= 1; i <= n; i++) {
        cout << par[i] << (i ==n ? "" : " ");
    }
    cout <<endl;
}
void do_second() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    int miss_idx = -1;
    int cur_xr = 0;

    for(int i =1; i <= n; i++) {
        cin >>a[i];
        if(a[i] == -1) {
            miss_idx = i;
        }
        else {
            cur_xr ^= a[i];
        }
    }
    if(miss_idx > 1) {
        a[miss_idx] = cur_xr;
    }

    for(int i= 2; i <=n; i++) {
        cout<< i << " " << a[i] << endl;
    }
}
void solve() {
    string phase ;
    cin >> phase;

    if(phase == "FIRST" ) {
        do_first();
    }
    else {
        do_second();
    }
}
int main() {
    fastio();

    int T = 1;
    // cin >> T;

    while(T--) {
        solve();
    }

    return 0;
}