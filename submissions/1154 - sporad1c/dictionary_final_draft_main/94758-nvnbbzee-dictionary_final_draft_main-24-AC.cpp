#include <bits/stdc++.h>
using namespace std;
struct Nd {
    int ch[2] = {0, 0};
    int ct = 0;
};
struct Tr {
    vector<Nd> tr;
    Tr(int n) {
        tr.reserve(60LL * n + 1);
        tr.emplace_back();
    }
    void clr() {
        tr.clear();
        tr.emplace_back();
    }
    void add(int x, int d) {
        int u = 0;
        tr[u].ct += d;
        for (int b = 29; b >= 0; --b) {
            int k = (x >> b) & 1;
            if (!tr[u].ch[k]) {
                tr[u].ch[k] = (int)tr.size();
                tr.emplace_back();
            }
            u = tr[u].ch[k];
            tr[u].ct += d;
        }
    }
    int ask(int x) {
        int u = 0, y = 0;
        for (int b = 29; b >= 0; --b) {
            int k = ((x >> b) & 1) ^ 1;
            int w = tr[u].ch[k];
            if (w && tr[w].ct > 0) {
                y |= 1 << b;
                u = w;
            } else {
                u = tr[u].ch[k ^ 1];
            }
        }
        return y;
    }
};
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1), v(n + 1), dg(n + 1);
        vector<int> f(n + 1), an(n + 1);
        vector<vector<int>> rv(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            ++dg[a[i]];
            rv[a[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++i) {
            cin >> v[i];
        }
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (!dg[i]) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (--dg[a[u]] == 0) {
                q.push(a[u]);
            }
        }
        vector<char> cy(n + 1), vs(n + 1);
        for (int i = 1; i <= n; ++i) {
            cy[i] = dg[i] > 0;
        }
        Tr tr(n);
        vector<pair<int, int>> st;
        for (int i = 1; i <= n; ++i) {
            if (!cy[i] || vs[i]) {
                continue;
            }
            vector<int> cc;
            int x = i;
            do {
                cc.push_back(x);
                vs[x] = 1;
                x = a[x];
            } while (x != i);
            int z = 0;
            f[cc[0]] = 0;
            for (int j = 0; j < (int)cc.size(); ++j) {
                int u = cc[j];
                z ^= v[u];
                if (j + 1 < (int)cc.size()) {
                    f[cc[j + 1]] = f[u] ^ v[u];
                }
            }
            tr.clr();
            for (int u : cc) {
                tr.add(f[u], 1);
                tr.add(f[u] ^ z, 1);
            }
            for (int u : cc) {
                an[u] = tr.ask(f[u]);
            }
            for (int u : cc) {
                for (int w : rv[u]) {
                    if (cy[w]) {
                        continue;
                    }
                    f[w] = f[u] ^ v[w];
                    st.push_back({w, 0});
                }
                while (!st.empty()) {
                    auto [w, d] = st.back();
                    st.pop_back();
                    if (d) {
                        tr.add(f[w], -1);
                    } else {
                        an[w] = tr.ask(f[w]);
                        tr.add(f[w], 1);
                        st.push_back({w, 1});
                        for (int y : rv[w]) {
                            f[y] = f[w] ^ v[y];
                            st.push_back({y, 0});
                        }
                    }
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (i > 1) {
                cout << ' ';
            }
            cout << an[i];
        }

        cout << '\n';
    }

    return 0;
}