#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int MAXN = 1000005;
int ans[MAXN];
ull w[MAXN];

int R[20005], C[20005], P[20005];

void solve() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return;

    for (int i = 0; i < q; ++i) cin >> R[i] >> C[i] >> P[i];

    int W = (m + 63) >> 6;
    fill(w, w + n * W, ~0ULL);
    fill(ans, ans + n * m, 0);

    for (int i = q - 1; i >= 0; --i) {
        int r0 = R[i], c0 = C[i], p = P[i];
        long long p2 = 1LL * p * p;

        for (int r = r0 - p; r <= r0 + p; ++r) {
            long long dr = r - r0;
            int dc = sqrt(p2 - dr * dr);
            int l = c0 - dc, r_bound = c0 + dc;

            int sw = l >> 6, ew = r_bound >> 6;
            int r_off = r * W;

            for (int k = sw; k <= ew; ++k) {
                int l_bit = (k == sw) ? (l & 63) : 0;
                int r_bit = (k == ew) ? (r_bound & 63) : 63;
                
                ull mask = (r_bit - l_bit == 63) ? ~0ULL : ((1ULL << (r_bit - l_bit + 1)) - 1) << l_bit;
                ull cur = w[r_off + k] & mask;
                if (!cur) {
                    w[r_off + k] &= ~mask;
                    continue;
                }

                while (cur) {
                    int b = __builtin_ctzll(cur);
                    int c = (k << 6) | b;
                    ans[r * m + c] = p2 - (dr * dr + 1LL * (c - c0) * (c - c0)) + 1;
                    cur &= cur - 1;
                }
                w[r_off + k] &= ~mask;
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            cout << ans[r * m + c] << (c == m - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    if (cin >> t) while (t--) solve();
}