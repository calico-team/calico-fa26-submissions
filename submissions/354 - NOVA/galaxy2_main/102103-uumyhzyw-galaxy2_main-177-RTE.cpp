#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n), v(n), d(n), h(n);
        for (int &x : a) {
            cin >> x;
            --x; // Use zero-based word numbers
            ++d[x];
        }
        for (int &x : v) cin >> x;

        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (d[i] == 0) q.push(i);

        vector<int> p;

        // Remove the words that lead into cycles
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            p.push_back(x);

            if (--d[a[x]] == 0)
                q.push(a[x]);
        }

        // The words left with positive indegree are on cycles
        vector<bool> seen(n, false);

        for (int i = 0; i < n; ++i) {
            if (d[i] == 0 || seen[i]) continue;

            vector<int> c;
            int x = i;

            do {
                c.push_back(x);
                seen[x] = true;
                x = a[x];
            } while (x != i);

            // Try stopping during the first two laps
            int best = 0;
            for (int s = 0; s < (int)c.size(); ++s) {
                int z = 0;
                for (int k = 0; k < 2 * (int)c.size(); ++k) {
                    z ^= v[c[(s + k) % c.size()]];
                    best = max(best, z);
                }
                h[c[s]] = best;
                best = 0; // Reset for the next starting word
            }
        }

        // Work backward from the cycles through the paths
        for (int j = (int)p.size() - 1; j >= 0; --j) {
            int x = p[j];
            h[x] = max(v[x], v[x] ^ h[a[x]]);
        }

        for (int i = 0; i < n; ++i)
            cout << h[i] << (i + 1 == n ? '\n' : ' ');
    }
}