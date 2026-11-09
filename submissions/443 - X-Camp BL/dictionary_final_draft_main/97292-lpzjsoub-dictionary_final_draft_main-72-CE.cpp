#include <bits/stdc++.h>
using namespace std;
struct nd {
    int next_nd;
    int weight;
};
void ip(int &n, vector<int> &a, vector<int> &v) {
    if (!(cin >> n)) return;
    a.resize(n);
    v.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
}
struct bs {
    int base[30];
    bs() {
        fill(base, base + 30, 0);
    }
    void insert(int mask) {
        for (int i = 29; i >= 0; --i) {
            if ((mask >> i) & 1) {
                if (!base[i]) {
                    base[i] = mask;
                    return;
                }
                mask ^= base[i];
            }
        }
    }
    int max_xor(int start) {
        int res = start;
        for (int i = 29; i >= 0; --i) {
            if ((res ^ base[i]) > res) {
                res ^= base[i];
            }
        }
        return res;
    }
};

void solve() {
    int n;
    vector<int> a, v;
    ip(n, a, v);
    if (n <= 0) return;
    vector<int> degg(n, 0);
    for (int i = 0; i < n; ++i) {
        degg[a[i]]++;
    }
    vector<int> q;
    for (int i = 0; i < n; ++i) {
        if (degg[i] == 0) {
            q.push_back(i);
        }
    }
    vector<bool> cic(n, true);
    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        cic[u] = false;
        int next_nd = a[u];
        degg[next_nd]--;
        if (degg[next_nd] == 0) {
            q.push_back(next_nd);
        }
    }
    vector<int> cid(n, -1);
    vector<bs> cycle_bs;
    int curcc = 0;
    for (int i = 0; i < n; ++i) {
        if (cic[i] && cid[i] == -1) {
            int curr = i;
            vector<int> nds;
            while (cid[curr] == -1) {
                cid[curr] = curcc;
                nds.push_back(curr);
                curr = a[curr];
            }

            int total_xor = 0;
            for (int nd : nds) {
                total_xor ^= v[nd];
            }

            bs b;
            b.insert(total_xor);

            int curx = 0;
            for (size_t j = 0; j < nds.size(); ++j) {
                b.insert(curx);
                curx ^= v[nds[j]];
            }

            cycle_bs.push_back(b);
            curcc++;
        }
    }

    vector<vector<int>> reva(n);
    for (int i = 0; i < n; ++i) {
        if (!cic[i]) {
            reva[a[i]].push_back(i);
        }
    }

    vector<int> ans(n, 0);
    vector<pair<int, int>> top;

    for (int i = 0; i < n; ++i) {
        if (cic[i]) {
            int cid = cid[i];
            ans[i] = cycle_bs[cid].max_xor(v[i]);
            top.push_back({i, v[i]});
        }
    }
    while (!top.empty()) {
        auto [u, curx] = top.back();
        top.pop_back();
        for (int child : reva[u]) {
            int nxtt = curx ^ v[child];
            int cid = cid[u];
            ans[child] = cycle_bs[cid].max_xor(nxtt);
            cid[child] = cid;
            top.push_back({child, nxtt});
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
}