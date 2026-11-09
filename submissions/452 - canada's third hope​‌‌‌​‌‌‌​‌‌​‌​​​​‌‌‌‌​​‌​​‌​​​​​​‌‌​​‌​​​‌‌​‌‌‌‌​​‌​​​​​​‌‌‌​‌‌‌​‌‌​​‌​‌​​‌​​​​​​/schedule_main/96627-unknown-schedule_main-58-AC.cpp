#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

const int inf = 0x3F3F3F3F;
const ll infll = 0x3F3F3F3F3F3F3F3FLL;

const int MM = 1e4+5;

vi adj[MM];
int par[MM], sz[MM];

void dfs(int u)
{
    sz[u] = 1;
    for (int v : adj[u])
    {
        dfs(v);
        sz[u] += sz[v];
    }
}

void solve()
{
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) { par[i] = sz[i] = 0; adj[i].clear(); }
    for (int i = 1; i <= n; i++)
    {
        int p; cin >> p;
        if (p) { adj[p].push_back(i); par[i] = p; }
    }
    priority_queue<pi> pq;
    for (int i = 1; i <= n; i++)
    {
        if (!par[i])
        {
            dfs(i);
            pq.push({ sz[i], i });
        }
    }
    int ans = 0;
    while (m-- > 0 && !pq.empty())
    {
        vi add;
        int cnt = 0;
        while (cnt < k && !pq.empty())
        {
            auto [_, u] = pq.top(); pq.pop();
            ans++; cnt++;
            for (int v : adj[u]) add.push_back(v);
        }
        for (int u : add) pq.push({ sz[u], u });
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int T; cin >> T;
    while (T-- > 0)
        solve();

    return 0;
}