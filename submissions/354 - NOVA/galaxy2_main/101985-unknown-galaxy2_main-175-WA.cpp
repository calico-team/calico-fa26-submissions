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

        vector<int> a(n), v(n);
        for (int &x : a) {
            cin >> x;
            --x; // Make the word numbers start at 0
        }
        for (int &x : v) cin >> x;

        vector<int> h(n), s(n, -1);
        vector<int> p;

        for (int i = 0; i < n; ++i) {
            if (s[i] != -1) continue;

            p.clear();
            int x = i;

            // Follow words until we hit an old path or a cycle
            while (s[x] == -1) {
                s[x] = i;
                p.push_back(x);
                x = a[x];
            }

            if (s[x] == i) {
                // The cycle's total XOR repeats every other lap
                int z = 0;
                int y = x;
                do {
                    z ^= v[y];
                    y = a[y];
                } while (y != x);

                int q = x;
                do {
                    h[q] = z;
                    q = a[q];
                } while (q != x);
            }

            // Work back through the path, keeping the best stopping point
            for (int j = (int)p.size() - 1; j >= 0; --j) {
                int y = p[j];
                if (s[y] == i && h[y] == 0) {
                    // Stopping here is always allowed
                    h[y] = v[y];
                    int z = a[y];
                    if (s[z] != i || z == y) {
                        // The next word's best result is already known
                        h[y] = max(h[y], v[y] ^ h[z]);
                    } else if (z != x) {
                        h[y] = max(h[y], v[y] ^ h[z]);
                    }
                }
            }

            // Mark this whole path as done
            for (int y : p) s[y] = -2;
        }

        for (int i = 0; i < n; ++i) {
            cout << h[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
}