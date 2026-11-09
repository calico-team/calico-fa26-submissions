#include <bits/stdc++.h>
#define all(c) begin(c), end(c)

using namespace std;
using ii = pair<int, int>;
using vi = vector<int>;

struct Query
{
    int r1, c1, r2, c2, k;
};

vi solve(vector<string> const &grid, vector<Query> const &queries)
{
    int n = (int)grid.size(), m = (int)grid[0].size();
    int k = (int)queries.size();
    int const INF = 1000000007;

    vector<vi> g(2 * n * m);
    auto id = [n](int r, int c, int p) { return 2 * (c * n + r) + p; };
    auto valid = [&](int r, int c, int p) {
        return grid[r][c] == '.' or grid[r][c] == (p ? 'R' : 'B');
    };
    auto add_edge = [&](int u, int v) { g[u].push_back(v), g[v].push_back(u); };

    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < m; ++c)
        {
            for (int p = 0; p < 2; ++p)
            {
                if (not valid(r, c, p))
                    continue;
                int u = id(r, c, p);
                if (r + 1 < n and valid(r + 1, c, p))
                    add_edge(u, id(r + 1, c, p));
                if (c + 1 < m and valid(r, c + 1, p))
                    add_edge(u, id(r, c + 1, p));
            }
            if (grid[r][c] == '.')
                add_edge(id(r, c, 0), id(r, c, 1));
        }
    }

    vector<ii> uv(k);
    for (int i = 0; i < k; ++i)
    {
        auto const &q = queries[i];
        uv[i] = {id(q.r1, q.c1, 0), id(q.r2, q.c2, 0)};
    }

    vi d(2 * n * m), ans(k, INF), order(k);
    iota(all(order), 0);
    auto bfs = [&](int s, int l, int r) {
        int lo = 2 * n * l, hi = 2 * n * (r + 1);
        fill(begin(d) + lo, begin(d) + hi, INF);
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while (not q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : g[u])
            {
                if (v < lo or v >= hi or d[v] != INF)
                    continue;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    };

    function<void(int, int, int, int)> dfs = [&](int l, int r, int ql, int qr) {
        if (l > r or ql == qr)
            return;
        int mid = (l + r) / 2;
        for (int x = 0; x < n; ++x)
        {
            for (int p = 0; p < 2; ++p)
            {
                if (not valid(x, mid, p))
                    continue;
                bfs(id(x, mid, p), l, r);
                for (int j = ql; j < qr; ++j)
                {
                    int i = order[j];
                    auto [u, v] = uv[i];
                    ans[i] = min(ans[i], d[u] + min(d[v], d[v ^ 1]));
                }
            }
        }

        auto first = begin(order) + ql, last = begin(order) + qr;
        auto left = partition(first, last, [&](int i) {
            return queries[i].c1 < mid and queries[i].c2 < mid;
        });
        auto right = partition(left, last, [&](int i) {
            return queries[i].c1 > mid and queries[i].c2 > mid;
        });
        int a = (int)(left - begin(order)), b = (int)(right - begin(order));
        dfs(l, mid - 1, ql, a);
        dfs(mid + 1, r, a, b);
    };
    dfs(0, m - 1, 0, k);
    return ans;
}

int main(void)
{
    ios::sync_with_stdio(false), cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> grid(n);
        for (auto &row : grid)
            cin >> row;
        vector<Query> queries(q);
        for (auto &[r1, c1, r2, c2, k] : queries)
            cin >> r1 >> c1 >> r2 >> c2 >> k;

        auto ans = solve(grid, queries);
        for (int i = 0; i < q; ++i)
            cout << (ans[i] <= queries[i].k ? "YES" : "NO") << '\n';
    }
    return 0;
}