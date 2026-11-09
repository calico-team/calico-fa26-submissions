#include <bits/stdc++.h>
using namespace std;

const int N = 200005, M = 6000000;
int n, a[N], v[N], s[N], ans[N], deg[N];
bool onCyc[N], seen[N];
vector<int> g[N];
int tr[M][2], cnt[M], tot;

void add(int x, int d) {
    int p = 0;
    for (int b = 29; b >= 0; b--) {
        int c = x >> b & 1;
        if (!tr[p][c]) {
            tr[p][c] = ++tot;
            tr[tot][0] = tr[tot][1] = cnt[tot] = 0;
        }
        p = tr[p][c];
        cnt[p] += d;
    }
}

int ask(int x) {
    int p = 0, r = 0;
    for (int b = 29; b >= 0; b--) {
        int c = (x >> b & 1) ^ 1;
        if (tr[p][c] && cnt[tr[p][c]]) r |= 1 << b, p = tr[p][c];
        else p = tr[p][c ^ 1];
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            g[i].clear();
            deg[i] = 0, onCyc[i] = 1, seen[i] = 0;
        }
        for (int i = 1; i <= n; i++) cin >> v[i];

        for (int i = 1; i <= n; i++) deg[a[i]]++;
        queue<int> q;
        for (int i = 1; i <= n; i++) if (!deg[i]) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            onCyc[u] = 0;
            if (--deg[a[u]] == 0) q.push(a[u]);
        }
        for (int i = 1; i <= n; i++) if (!onCyc[i]) g[a[i]].push_back(i);

        for (int i = 1; i <= n; i++) {
            if (!onCyc[i] || seen[i]) continue;
            vector<int> cyc;
            for (int u = i; !seen[u]; u = a[u]) seen[u] = 1, cyc.push_back(u);
            int k = cyc.size();
            s[cyc[k - 1]] = v[cyc[k - 1]];
            for (int j = k - 2; j >= 0; j--) s[cyc[j]] = v[cyc[j]] ^ s[cyc[j + 1]];
            int X = s[cyc[0]];

            tot = 0;
            tr[0][0] = tr[0][1] = 0;
            for (int c : cyc) add(s[c], 1), add(s[c] ^ X, 1);
            for (int c : cyc) ans[c] = ask(s[c]);

            vector<int> st;
            for (int c : cyc) for (int u : g[c]) st.push_back(u);
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                if (u < 0) { add(s[~u], -1); continue; }
                s[u] = v[u] ^ s[a[u]];
                ans[u] = ask(s[u]);
                add(s[u], 1);
                st.push_back(~u);
                for (int w : g[u]) st.push_back(w);
            }
        }

        for (int i = 1; i <= n; i++) cout << ans[i] << (i == n ? '\n' : ' ');
    }
}
