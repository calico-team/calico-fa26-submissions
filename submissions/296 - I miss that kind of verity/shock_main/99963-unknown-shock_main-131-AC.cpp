#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pull = pair<ull, ull>;

struct Query {
    int r, c, p;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<Query> queries(q);
        for (int i = 0; i < q; i++) {
            cin >> queries[i].r >> queries[i].c >> queries[i].p;
        }

        bool rev = n > m;
        if (rev) {
            swap(n, m);
            for (auto &query : queries) {
                swap(query.r, query.c);
            }
        }

        vector<vector<int>> ans(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            vector<pii> intervals(q);


            vector<int> parent(m);
            vector<pii> components(m);
            for (int j = 0; j < m; j++) {
                parent[j] = j;
                components[j] = {j, j};
            }

            function<int(int)> find = [&](int x) {
                return parent[x] == x ? x : parent[x] = find(parent[x]);
            };

            auto unite = [&](int x, int y) {
                x = find(x);
                y = find(y);
                if (x == y) return;
                int s1 = components[x].second - components[x].first + 1;
                int s2 = components[y].second - components[y].first + 1;
                if (s1 < s2) swap(x, y);

                parent[y] = x;
                components[x].first = min(components[x].first, components[y].first);
                components[x].second = max(components[x].second, components[y].second);
            };



            for (int j = q - 1; j >= 0; j--) {
                auto [r, c, p] = queries[j];
                ll var = ((ll) p * p - (ll) (r - i) * (r - i));
                if (var < 0) continue;
                var = sqrt(var);
                int _l = max(0, c - (int) var);
                int _r = min(m - 1, c + (int) var);
                while (_l <= _r) {
                    if (ans[i][_l] == 0) {
                        ans[i][_l] = (ll) p * p - (ll) (r - i) * (r - i) - (ll) (_l - c) * (_l - c) + 1;
                        if (_l > 0 && ans[i][_l - 1] > 0) {
                            unite(_l, _l - 1);
                        }
                        if (_l < m - 1 && ans[i][_l + 1] > 0) {
                            unite(_l, _l + 1);
                        }
                    }
                    else {
                        _l = components[find(_l)].second + 1;
                    }
                }
            }
        }



        if (!rev) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[i][j] << ' ';
                }
                cout << '\n';
            }
        }
        else {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << ans[j][i] << ' ';
                }
                cout << '\n';
            }
        }
    }

}