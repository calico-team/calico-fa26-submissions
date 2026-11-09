#include <bits/stdc++.h>
using namespace std;

struct BinaryTrie {
    struct Node {
        int ch[2], cnt;
        Node() : ch{-1, -1}, cnt(0) {}
    };

    vector<Node> nodes;

    BinaryTrie() {
        nodes.emplace_back();
    }

    void reset() {
        nodes.clear();
        nodes.emplace_back();
    }

    void update(int x, int change) {
        int cur = 0;
        nodes[cur].cnt += change;

        for (int b = 29; b >= 0; b--) {
            int dir = (x >> b) & 1;
            int nxt = nodes[cur].ch[dir];

            if (nxt == -1) {
                nxt = nodes.size();
                nodes[cur].ch[dir] = nxt;
                nodes.emplace_back();
            }

            cur = nxt;
            nodes[cur].cnt += change;
        }
    }

    int best(int x) const {
        int cur = 0, result = 0;

        for (int b = 29; b >= 0; b--) {
            int want = 1 - ((x >> b) & 1);
            int nxt = nodes[cur].ch[want];

            if (nxt != -1 && nodes[nxt].cnt > 0) {
                cur = nxt;
                result |= 1 << b;
            } else {
                cur = nodes[cur].ch[want ^ 1];
            }
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> to(N), val(N), deg(N, 0);
        vector<vector<int>> rev(N);

        for (int i = 0; i < N; i++) {
            cin >> to[i];
            --to[i];

            deg[to[i]]++;
            rev[to[i]].push_back(i);
        }

        for (int &v : val)
            cin >> v;

        queue<int> q;

        for (int i = 0; i < N; i++)
            if (deg[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (--deg[to[u]] == 0)
                q.push(to[u]);
        }

        vector<char> seen(N, false);
        vector<int> pref(N, 0), ans(N, 0);

        BinaryTrie trie;

        for (int start = 0; start < N; start++) {
            if (deg[start] == 0 || seen[start])
                continue;

            vector<int> cycle;
            int w = 0, u = start;

            do {
                seen[u] = true;
                pref[u] = w;
                cycle.push_back(u);

                w ^= val[u];
                u = to[u];
            } while (u != start);

            trie.reset();

            for (int v : cycle) {
                trie.update(pref[v], 1);

                if (w != 0)
                    trie.update(pref[v] ^ w, 1);
            }

            for (int v : cycle)
                ans[v] = trie.best(pref[v]);

            vector<int> events;

            for (int v : cycle) {
                for (int child : rev[v]) {
                    if (deg[child] == 0)
                        events.push_back(child);
                }
            }

            while (!events.empty()) {
                int v = events.back();
                events.pop_back();

                if (v >= 0) {
                    pref[v] = pref[to[v]] ^ val[v];
                    ans[v] = trie.best(pref[v]);

                    trie.update(pref[v], 1);
                    events.push_back(~v);

                    for (int child : rev[v])
                        events.push_back(child);
                } else {
                    v = ~v;
                    trie.update(pref[v], -1);
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (i) cout << ' ';
            cout << ans[i];
        }

        cout << '\n';
    }

    return 0;
}
