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

const int MM = 2e5+5;

vi adj[MM];
int a[MM];

void dfs(int u, int p)
{
    if (p) a[u] = p;
    for (int v : adj[u])
    {
        if (v == p) continue;
        dfs(v, u);
    }
}

void first()
{
    int n; cin >> n;
    for (int i = 0; i < n-1; i++)
    {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    int xsum = 0;
    for (int i = 2; i <= n; i++) xsum ^= a[i];
    a[1] = xsum;
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << "\n";
}

void second()
{
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (a[1] != -1)
    {
        int xsum = 0;
        for (int i = 2; i <= n; i++)
        {
            if (a[i] != -1)
                xsum ^= a[i];
        }
        for (int i = 2; i <= n; i++)
        {
            if (a[i] == -1)
                a[i] = a[1]^xsum;
        }
    }
    for (int i = 2; i <= n; i++) cout << i << " " << a[i] << "\n";
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    string type; cin >> type;
    if (type == "FIRST") first();
    else second();

    return 0;
}