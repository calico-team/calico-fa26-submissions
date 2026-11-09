#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> g(N);
        string flat;
        for (int i = 0; i < N; i++) {
            string row;
            cin >> row;
            flat += row;
        }
        int S = N * M;
        // state = cell*2 + mode ; mode 0 = blue, 1 = red
        vector<int> comp(2 * S, -1);
        auto active = [&](int cell, int m) {
            char ch = flat[cell];
            return ch == '.' || (ch == 'B' && m == 0) || (ch == 'R' && m == 1);
        };
        int cid = 0;
        vector<int> st;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        for (int cell = 0; cell < S; cell++) {
            for (int m = 0; m < 2; m++) {
                int s = cell * 2 + m;
                if (comp[s] != -1 || !active(cell, m)) continue;
                comp[s] = cid;
                st.push_back(s);
                while (!st.empty()) {
                    int cur = st.back();
                    st.pop_back();
                    int c = cur >> 1, md = cur & 1;
                    int r = c / M, col = c % M;
                    if (flat[c] == '.') {
                        int o = c * 2 + (1 - md);
                        if (comp[o] == -1) {
                            comp[o] = cid;
                            st.push_back(o);
                        }
                    }
                    for (int k = 0; k < 4; k++) {
                        int nr = r + dr[k], nc = col + dc[k];
                        if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                        int nb = nr * M + nc;
                        int ns = nb * 2 + md;
                        if (comp[ns] == -1 && active(nb, md)) {
                            comp[ns] = cid;
                            st.push_back(ns);
                        }
                    }
                }
                cid++;
            }
        }
        while (Q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            int a = comp[(rs * M + cs) * 2];
            int t = re * M + ce;
            bool ok = a != -1 && (comp[t * 2] == a || comp[t * 2 + 1] == a);
            cout << (ok ? "YES" : "NO") << "\n";
        }
    }
}
