#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return;
    vector<int> grid(N * M, 0);
    for (int q = 0; q < Q; ++q) {
        ll R, C, P; cin >> R >> C >> P;
        ll pq = P * P;
        ll pq11 = pq + 1;
        for (ll dr = -P; dr <= P; ++dr) {
            ll r = R + dr;
            ll dr_sq = dr * dr;
            ll mdc = static_cast<ll>(sqrt(pq - dr_sq));
            int ovrld = r * M;
            for (ll dc = -mdc; dc <= mdc; ++dc) {
                ll c = C + dc;
                grid[ovrld + c] = pq11 - (dr_sq + dc * dc);
            }
        }
    }

    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < M; ++c) {
            cout << grid[r * M + c] << (c == M - 1 ? "" : " ");
        }
        cout << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}