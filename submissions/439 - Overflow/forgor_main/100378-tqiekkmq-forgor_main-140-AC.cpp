#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;
int p[MAXN], a[MAXN];

inline void add_edge(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    string type;
    if (!(cin >> type)) return 0;
    int n; cin >> n;

    if (type[0] == 'F') { // FIRST
        for (int i = 0, u, v; i < n - 1; ++i) {
            cin >> u >> v;
            add_edge(u, v);
        }

        // BFS to determine parent pointers rooted at 1
        static int q[MAXN];
        int l = 0, r = 0;
        q[r++] = 1;

        while (l < r) {
            int u = q[l++];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (v != 1 && !p[v]) {
                    p[v] = u;
                    q[r++] = v;
                }
            }
        }

        // Checksum in a[1], parents in a[2..n]
        int s = 0;
        for (int i = 2; i <= n; ++i) s ^= (a[i] = p[i]);
        a[1] = s;

        for (int i = 1; i <= n; ++i) 
            cout << a[i] << " \n"[i == n];
    } else { // SECOND
        int bad = -1, s = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] < 0) bad = i;
            else s ^= a[i];
        }
        a[bad] = s;

        for (int i = 2; i <= n; ++i) 
            cout << i << ' ' << a[i] << '\n';
    }
    return 0;
}