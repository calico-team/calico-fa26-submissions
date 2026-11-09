#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi adj[10005];
int height[10005], par[10005];

void dfs(int u) {
    height[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
        height[u] = max(height[u], height[v] + 1);
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    rep(i, 1, n+1) {
        adj[i].clear();
    }

    rep(i, 1, n+1) {
        int p; cin >> p;
        adj[p].pb(i);
        par[i] = p;
    }
    dfs(0);

    priority_queue<pii> pq;
    rep(u, 1, n+1) {
        if (par[u] == 0)
            pq.emplace(height[u], u);
    }

    int ans = 0;
    rep(i, 0, m) {
        int l = min(k, sz(pq));
        while (l--) {
            ++ans;
            auto [depth, u] = pq.top(); pq.pop();
            for (int v : adj[u]) {
                pq.emplace(height[v], v);
            }
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t = 1; cin >> t;
    while (t--) solve();
}
