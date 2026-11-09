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

int nxt[MM], V[MM], trie[32*MM][2], cnt[32*MM], id, ANS[MM];
bool vis[MM], incyc[MM];
vi rev[MM];
int n;

void upd(int x, int y)
{
    for (int i = 30, v = 0; i >= 0; i--)
    {
        int b = 1&x>>i;
        if (trie[v][b] == -1) trie[v][b] = ++id;
        v = trie[v][b]; cnt[v] += y;
    }
}

int qry(int x)
{
    int ans = 0;
    for (int i = 30, v = 0; i >= 0; i--)
    {
        int b = !(1&x>>i);
        if (trie[v][b] == -1 || cnt[trie[v][b]] == 0) v = trie[v][!b];
        else
        {
            ans += 1<<i;
            v = trie[v][b];
        }
    }
    return ans;
}

vi getcyc(int i)
{
    int s=nxt[i], f=nxt[s];
    while (s != f) { s = nxt[s]; f = nxt[nxt[f]]; }
    s = i;
    while (s != f) { s = nxt[s]; f = nxt[f]; }
    vi cyc = { s }; incyc[s] = 1;
    for (s=nxt[s]; s != f; s=nxt[s])
    {
        cyc.push_back(s);
        incyc[s] = 1;
    }
    return cyc;
}

void dfs(int rt, int psum_rt)
{
    stack<array<int, 3>> stk;
    stk.push({ rt, psum_rt, 0 });
    while (!stk.empty())
    {
        auto [u, psum, _] = stk.top(); stk.pop();
        if (_)
        {
            upd(psum, -1);
            continue;
        }
        vis[u] = 1;
        psum ^= V[u];
        upd(psum, 1);
        ANS[u] = max(ANS[u], qry(psum));
        stk.push({ u, psum, 1 });
        for (int v : rev[u])
        {
            if (incyc[v]) continue;
            stk.push({ v, psum, 0 });
        }
    }
}

void dfs2(int rt, int psum_rt)
{
    stack<pi> stk;
    stk.push({ rt, psum_rt });
    while (!stk.empty())
    {
        auto [u, psum] = stk.top(); stk.pop();
        psum ^= V[u];
        ANS[u] = max(ANS[u], qry(psum));
        for (int v : rev[u])
        {
            if (incyc[v]) continue;
            stk.push({ v, psum });
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++) { vis[i] = incyc[i] = 0; ANS[i] = 0; rev[i].clear(); }
    for (int i = 1; i <= n; i++)
    {
        cin >> nxt[i];
        rev[nxt[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) cin >> V[i];
    for (int s = 1; s <= n; s++)
    {
        if (vis[s]) continue;
        vi cyc = getcyc(s);
        for (int rt : cyc)
        {
            upd(0, 1);
            dfs(rt, 0);
            upd(0, -1);
        }
        vi rep = cyc;
        for (int _ = 0; _ < 3; _++) rep.insert(rep.end(), cyc.begin(), cyc.end());
        vi pre(rep.size());
        for (int i = 0, psum = 0; i < (int)rep.size(); i++)
        {
            psum ^= V[rep[i]];
            upd(psum, 1);
            pre[i] = psum;
        }
        for (int i = 0; i < (int)rep.size(); i++)
        {
            int rt = rep[i];
            dfs2(rt, pre[i]);
            upd(pre[i], -1);
        }
    }
    for (int i = 1; i <= n; i++) cout << ANS[i] << " ";
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    memset(trie, -1, sizeof(trie));
    int T; cin >> T;
    while (T-- > 0)
        solve();

    return 0;
}