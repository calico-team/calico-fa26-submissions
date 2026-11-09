#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node {
        int ch[2] = {0, 0};
        int cnt = 0;
    };
    vector<Node> t;
    Trie() { t.emplace_back(); }

    void insert(int val) {
        int u = 0;
        t[u].cnt++;
        for (int b = 29; b >= 0; b--) {
            int bit = (val >> b) & 1;
            if (!t[u].ch[bit]) {
                t[u].ch[bit] = t.size();
                t.emplace_back();
            }
            u = t[u].ch[bit];
            t[u].cnt++;
        }
    }

    void remove(int val) {
        int u = 0;
        t[u].cnt--;
        for (int b = 29; b >= 0; b--) {
            int bit = (val >> b) & 1;
            u = t[u].ch[bit];
            t[u].cnt--;
        }
    }

    int query_max(int val) {
        int u = 0, res = 0;
        for (int b = 29; b >= 0; b--) {
            int bit = (val >> b) & 1;
            int want = 1 - bit;
            if (t[u].ch[want] && t[t[u].ch[want]].cnt > 0) {
                res |= (1 << b);
                u = t[u].ch[want];
            } else {
                u = t[u].ch[bit];
            }
        }
        return res;
    }
};

vector<int> solve(int N, vector<int> A, vector<int> V) {
    for (int& x : A) x--; // to 0-indexed
    vector<vector<int>> rev(N);
    vector<int> in_deg(N, 0);
    for (int i = 0; i < N; i++) {
        rev[A[i]].push_back(i);
        in_deg[A[i]]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (in_deg[i] == 0) q.push(i);
    }
    vector<bool> in_cycle(N, true);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        in_cycle[u] = false;
        if (--in_deg[A[u]] == 0) q.push(A[u]);
    }

    vector<int> ans(N, 0);
    vector<bool> visited_cycle(N, false);

    for (int i = 0; i < N; i++) {
        if (!in_cycle[i] || visited_cycle[i]) continue;
        vector<int> cycle;
        int curr = i;
        while (!visited_cycle[curr]) {
            visited_cycle[curr] = true;
            cycle.push_back(curr);
            curr = A[curr];
        }

        int L = cycle.size();
        vector<int> pref(L);
        int running = 0;
        for (int j = 0; j < L; j++) {
            running ^= V[cycle[j]];
            pref[j] = running;
        }
        int W = running;

        Trie trie;
        for (int j = 0; j < L; j++) {
            trie.insert(pref[j]);
            trie.insert(pref[j] ^ W);
        }

        for (int j = 0; j < L; j++) {
            int prev_pref = (j == 0 ? 0 : pref[j - 1]);
            ans[cycle[j]] = trie.query_max(prev_pref);
        }

        auto dfs = [&](auto& self, int u, int F_u) -> void {
            ans[u] = trie.query_max(F_u);
            trie.insert(F_u);
            for (int p : rev[u]) {
                if (!in_cycle[p]) {
                    self(self, p, F_u ^ V[p]);
                }
            }
            trie.remove(F_u);
        };

        for (int j = 0; j < L; j++) {
            int c_node = cycle[j];
            for (int p : rev[c_node]) {
                if (!in_cycle[p]) {
                    int prev_pref = (j == 0 ? 0 : pref[j - 1]);
                    trie.insert(prev_pref);
                    dfs(dfs, p, prev_pref ^ V[p]);
                    trie.remove(prev_pref);
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; if (!(cin >> T)) return 0;
    while (T--) {
        int N; cin >> N;
        vector<int> A(N), V(N);
        for (int& i : A) cin >> i;
        for (int& i : V) cin >> i;
        vector<int> ans = solve(N, A, V);
        for (int& i : ans) cout << i << ' ';
        cout << '\n';
    }
}