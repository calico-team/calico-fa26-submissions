#include <bits/stdc++.h>
using namespace std;

struct XorTrie {
    vector<array<int, 2>> ch;
    vector<int> cnt;
    int nn;

    void reset() {
        nn = 1;
        if (ch.empty()) {
            ch.push_back({0, 0});
            cnt.push_back(0);
        }
        ch[0] = {0, 0};
        cnt[0] = 0;
    }

    int newNode() {
        if (nn == (int)ch.size()) {
            ch.push_back({0, 0});
            cnt.push_back(0);
        }
        ch[nn] = {0, 0};
        cnt[nn] = 0;
        return nn++;
    }

    void add(int x, int delta) {
        int p = 0;
        cnt[p] += delta;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            if (!ch[p][bit]) ch[p][bit] = newNode();
            p = ch[p][bit];
            cnt[p] += delta;
        }
    }

    int query(int x) const {
        int p = 0, res = 0;
        for (int b = 29; b >= 0; --b) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            if (ch[p][want] && cnt[ch[p][want]] > 0) {
                res |= (1 << b);
                p = ch[p][want];
            } else {
                p = ch[p][bit];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    XorTrie ct, pt;
    ct.reset();
    pt.reset();

    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N), V(N);
        for (auto &x : A) {
            cin >> x;
            --x;
        }
        for (auto &x : V) cin >> x;

        vector<int> indeg(N, 0);
        for (int u = 0; u < N; ++u) ++indeg[A[u]];

        vector<char> onCyc(N, 1);
        queue<int> q;
        for (int u = 0; u < N; ++u) {
            if (indeg[u] == 0) q.push(u);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            onCyc[u] = 0;
            if (--indeg[A[u]] == 0) q.push(A[u]);
        }

        vector<vector<int>> rev(N);
        for (int u = 0; u < N; ++u) {
            if (!onCyc[u]) rev[A[u]].push_back(u);
        }

        vector<int> F(N), ans(N);
        vector<char> vis(N, 0);

        for (int i = 0; i < N; ++i) {
            if (!onCyc[i] || vis[i]) continue;

            vector<int> cyc;
            int u = i;
            do {
                vis[u] = 1;
                cyc.push_back(u);
                u = A[u];
            } while (u != i);

            int m = (int)cyc.size();
            vector<int> Q(m);
            int cur = 0;
            for (int j = 0; j < m; ++j) {
                Q[j] = cur;
                cur ^= V[cyc[j]];
            }
            int C = cur;

            ct.reset();
            for (int j = 0; j < m; ++j) ct.add(Q[j], +1);

            auto cycQuery = [&](int y) {
                return max(ct.query(y), ct.query(y ^ C));
            };

            for (int s = 0; s < m; ++s) {
                ans[cyc[s]] = cycQuery(Q[s]);
            }

            pt.reset();
            pt.add(0, +1);

            for (int s = 0; s < m; ++s) {
                int entryQ = Q[s];
                for (int root : rev[cyc[s]]) {
                    vector<pair<int, int>> st;
                    st.push_back({root, 0});

                    while (!st.empty()) {
                        auto [x, ph] = st.back();
                        st.pop_back();

                        if (ph == 1) {
                            pt.add(F[x], -1);
                            continue;
                        }

                        int nxt = A[x];
                        F[x] = V[x] ^ (onCyc[nxt] ? 0 : F[nxt]);
                        ans[x] = max(pt.query(F[x]), cycQuery(F[x] ^ entryQ));

                        pt.add(F[x], +1);
                        st.push_back({x, 1});
                        for (int v : rev[x]) st.push_back({v, 0});
                    }
                }
            }
        }

        for (int u = 0; u < N; ++u) {
            cout << ans[u] << (u + 1 == N ? '\n' : ' ');
        }
    }

    return 0;
}
