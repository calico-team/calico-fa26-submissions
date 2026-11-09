#include <bits/stdc++.h>

using namespace std;
using ii = pair<int, int>;
using vi = vector<int>;

struct BitTrie
{
    int                  n;
    vector<array<int, 2>> t;
    vi                   cnt;

    BitTrie(int k) : n(0), t(1), cnt(1, 0)
    {
        int capacity = 1;
        for (int b = 1; b <= 30; ++b)
            capacity += min(k, 1 << b);
        t.reserve(capacity);
        cnt.reserve(capacity);
    }

    int new_node()
    {
        t.push_back({0, 0});
        cnt.push_back(0);
        return ++n;
    }

    void clear()
    {
        n = 0;
        t.resize(1);
        t[0] = {0, 0};
        cnt.resize(1);
        cnt[0] = 0;
    }

    void add(int a, int delta)
    {
        int cur = 0;
        for (int b = 29; b >= 0; --b)
        {
            int x = (a >> b) & 1;
            if (not t[cur][x])
                t[cur][x] = new_node();
            cur = t[cur][x];
            cnt[cur] += delta;
        }
    }

    int query(int a) const
    {
        int cur = 0, ans = 0;
        for (int b = 29; b >= 0; --b)
        {
            int x = (a >> b) & 1;
            int nxt = t[cur][x ^ 1];
            if (nxt and cnt[nxt] > 0)
                ans |= 1 << b, cur = nxt;
            else
                cur = t[cur][x];
        }
        return ans;
    }
};

vi solve(const vi &a, const vi &v)
{
    int n = (int)a.size();
    vector<vi> gr(n);
    vi deg(n, 0), vis(n, 0), p(n), ans(n);
    for (int u = 0; u < n; ++u)
        gr[a[u]].push_back(u), ++deg[a[u]];

    queue<int> q;
    for (int u = 0; u < n; ++u)
        if (deg[u] == 0)
            q.push(u);
    while (not q.empty())
    {
        int u = q.front();
        q.pop();
        if (--deg[a[u]] == 0)
            q.push(a[u]);
    }

    BitTrie trie(2 * n);
    vector<ii> st;
    st.reserve(n);
    for (int s = 0; s < n; ++s)
    {
        if (deg[s] == 0 or vis[s])
            continue;

        vi cycle;
        int u = s, acc = 0;
        do
        {
            vis[u] = 1;
            cycle.push_back(u);
            p[u] = acc;
            acc ^= v[u];
            u = a[u];
        } while (u != s);

        trie.clear();
        for (int w : cycle)
        {
            trie.add(p[w], 1);
            if (acc)
                trie.add(p[w] ^ acc, 1);
        }

        for (int w : cycle)
        {
            ans[w] = trie.query(p[w]);
            for (int x : gr[w])
            {
                if (deg[x])
                    continue;
                p[x] = v[x] ^ p[w];
                st.emplace_back(x, 0);
            }
        }

        while (not st.empty())
        {
            auto [w, exit] = st.back();
            st.pop_back();
            if (exit)
            {
                trie.add(p[w], -1);
                continue;
            }

            ans[w] = trie.query(p[w]);
            trie.add(p[w], 1);
            st.emplace_back(w, 1);
            for (int x : gr[w])
            {
                p[x] = v[x] ^ p[w];
                st.emplace_back(x, 0);
            }
        }
    }
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false), cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vi a(n), v(n);
        for (int &ai : a)
            cin >> ai, --ai;
        for (int &x : v)
            cin >> x;
        vi ans = solve(a, v);
        for (int i = 0; i < n; ++i)
            cout << ans[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}