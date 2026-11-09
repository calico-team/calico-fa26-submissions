#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

/** for blitz */
// ifstream cin("input.txt");
// ofstream cout("output.txt");

void dfs(int cur, int dist, vi &d, vector<vi> &adj) {
    d[cur] = dist;
    for (auto v: adj[cur]) dfs(v, dist+1, d, adj);
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    
    vi p(n+1);
    rep(i, 1, n+1) cin >> p[i];

    vi d(n+1);
    vector<vi> suc(n+1);
    rep(i, 1, n+1) {
        if (p[i] > 0)
            suc[p[i]].push_back(i);
    }

    rep(i, 1, n+1) {
        if (p[i] == 0) {
            dfs(i, 0, d, suc);
        }
    }

    vi meow(m);
    rep(i, 1, n+1) {
        if (d[i] < m)
            meow[d[i]]++;
    }

    int ans = 0;
    rep(i, 0, m) {
        ans += min(meow[i], k);
    }

    cout << min(ans, m * k) << endl;

}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}