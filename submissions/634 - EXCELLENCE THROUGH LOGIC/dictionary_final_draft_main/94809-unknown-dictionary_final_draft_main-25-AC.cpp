
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int ch[2] = {0, 0};
    int cnt = 0;
};

struct Trie {
    vector<Node> t;
    int freeHead = 0;

    Trie(int capacity = 0) {
        t.reserve(capacity);
        t.push_back(Node());
        t.push_back(Node());
    }

    int alloc() {
        if (freeHead) {
            int x = freeHead;
            freeHead = t[x].ch[0];
            t[x] = Node();
            return x;
        }

        t.push_back(Node());
        return (int)t.size() - 1;
    }

    void insert(int x) {
        int u = 1;
        t[u].cnt++;

        for (int b = 29; b >= 0; --b) {
            int z = (x >> b) & 1;

            if (!t[u].ch[z]) {
                t[u].ch[z] = alloc();
            }

            u = t[u].ch[z];
            t[u].cnt++;
        }
    }

    void erase(int x) {
        int path[31], dir[30];
        int u = 1;
        path[0] = u;

        for (int k = 0, b = 29; b >= 0; --b, ++k) {
            int z = (x >> b) & 1;
            dir[k] = z;
            u = t[u].ch[z];
            path[k + 1] = u;
        }

        for (int k = 29; k >= 0; --k) {
            int v = path[k + 1];
            t[v].cnt--;

            if (t[v].cnt == 0) {
                int p = path[k];
                t[p].ch[dir[k]] = 0;

                t[v].ch[0] = freeHead;
                t[v].ch[1] = 0;
                freeHead = v;
            }
        }

        t[1].cnt--;
    }

    int maxxor(int x) const {
        int u = 1;
        int result = 0;

        for (int b = 29; b >= 0; --b) {
            int z = (x >> b) & 1;
            int wanted = z ^ 1;
            int v = t[u].ch[wanted];

            if (v && t[v].cnt > 0) {
                result |= (1 << b);
                u = v;
            } else {
                u = t[u].ch[z];
            }
        }

        return result;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> nxt(n), val(n), indeg(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> nxt[i];
        --nxt[i];
        indeg[nxt[i]]++;
    }

    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }

    vector<int> head(n, -1), to(n), ne(n);

    for (int u = 0; u < n; ++u) {
        int v = nxt[u];
        to[u] = u;
        ne[u] = head[v];
        head[v] = u;
    }

    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order.push_back(u);

        int v = nxt[u];

        if (--indeg[v] == 0) {
            q.push(v);
        }
    }

    vector<char> seen(n, false);
    vector<int> ans(n, 0);

    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0 || seen[i]) {
            continue;
        }

        vector<int> cyc;
        int u = i;
        int cycleXor = 0;

        while (!seen[u]) {
            seen[u] = true;
            cyc.push_back(u);
            cycleXor ^= val[u];
            u = nxt[u];
        }

        int L = (int)cyc.size();
        int limit = (cycleXor == 0 ? L : 2 * L);

        vector<int> pref(L + limit, 0);

        for (int k = 0; k < (int)pref.size() - 1; ++k) {
            pref[k + 1] = pref[k] ^ val[cyc[k % L]];
        }

        Trie cycleTrie(30 * limit + 2);
        Trie pathTrie(30 * (n - L + 1) + 2);

        pathTrie.insert(0);

        for (int k = 1; k <= limit; ++k) {
            cycleTrie.insert(pref[k]);
        }

        struct State {
            int u, px;
            bool exit;
        };

        vector<State> st;

        for (int j = 0; j < L; ++j) {
            int root = cyc[j];
            int offset = pref[j];

            ans[root] = cycleTrie.maxxor(offset);

            for (int e = head[root]; e != -1; e = ne[e]) {
                int x = to[e];

                if (indeg[x] == 0) {
                    st.push_back({x, val[x], false});
                }
            }

            while (!st.empty()) {
                State cur = st.back();
                st.pop_back();

                if (cur.exit) {
                    pathTrie.erase(cur.px);
                    continue;
                }

                int treeBest = pathTrie.maxxor(cur.px);
                int cycleBest = cycleTrie.maxxor(offset ^ cur.px);

                ans[cur.u] = max(treeBest, cycleBest);

                pathTrie.insert(cur.px);

                st.push_back({cur.u, cur.px, true});

                for (int e = head[cur.u]; e != -1; e = ne[e]) {
                    int y = to[e];

                    if (indeg[y] == 0) {
                        st.push_back({
                            y,
                            cur.px ^ val[y],
                            false
                        });
                    }
                }
            }

            if (j + 1 < L) {
                cycleTrie.erase(pref[j + 1]);
                cycleTrie.insert(pref[j + limit + 1]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }

    cout << '\n';
}

void read_your_input() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dinosauraus = 0;

    read_your_input();

    return dinosauraus;
}
