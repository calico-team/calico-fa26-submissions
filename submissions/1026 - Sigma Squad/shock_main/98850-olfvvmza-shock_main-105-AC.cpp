#include <bits/stdc++.h>
using namespace std;

vector<int> nxt;

int find(int x) {
    int r = x;
    while (nxt[r] != r) r = nxt[r];
    while (nxt[x] != r) {
        int y = nxt[x];
        nxt[x] = r;
        x = y;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    string out;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<int> R(q), C(q), P(q);
        for (int i = 0; i < q; i++) cin >> R[i] >> C[i] >> P[i];

        int w = m + 1;
        nxt.resize((size_t)n * w);
        for (int i = 0; i < n * w; i++) nxt[i] = i;
        vector<int> val((size_t)n * m, 0);

        for (int i = q - 1; i >= 0; i--) {
            long long p2 = 1LL * P[i] * P[i];
            for (int dr = -P[i]; dr <= P[i]; dr++) {
                long long rem = p2 - 1LL * dr * dr;
                long long h = sqrtl(rem);
                while (h * h > rem) h--;
                while ((h + 1) * (h + 1) <= rem) h++;
                int r = R[i] + dr;
                int lo = C[i] - h, hi = C[i] + h;
                int c = find(r * w + lo) - r * w;
                while (c <= hi) {
                    long long dc = c - C[i];
                    val[(size_t)r * m + c] = p2 - dr * dr - dc * dc + 1;
                    nxt[r * w + c] = r * w + c + 1;
                    c = find(r * w + c + 1) - r * w;
                }
            }
        }

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (c) out += ' ';
                out += to_string(val[(size_t)r * m + c]);
            }
            out += '\n';
        }
    }
    cout << out;
    return 0;
}
