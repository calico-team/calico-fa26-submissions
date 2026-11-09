#include <bits/stdc++.h>
using namespace std;

struct Earthquake {
    int r, c, p;
};

int findNext(int x, vector<int>& nxt) {
    while (nxt[x] != x) {
        nxt[x] = nxt[nxt[x]];
        x = nxt[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<Earthquake> events(Q);
        for (auto& e : events)
            cin >> e.r >> e.c >> e.p;

        int total = N * M;
        vector<int> ans(total, 0), nxt(total + 1);
        iota(nxt.begin(), nxt.end(), 0);

        for (int k = Q - 1; k >= 0; --k) {
            auto [r, c, p] = events[k];
            int power2 = p * p;

            for (int dr = -p; dr <= p; ++dr) {
                int rem = power2 - dr * dr;
                if (rem < 0) continue;
                int dc = (int)sqrt((double)rem);

                while ((dc + 1) * (dc + 1) <= rem) ++dc;
                while (dc * dc > rem) --dc;

                int start = (r + dr) * M;
                if (r + dr < 0 || r + dr >= N) continue;
                
                int left_bound = max(0, c - dc);
                int right_bound = min(M - 1, c + dc);
                
                if (left_bound > right_bound) continue;

                int right = start + right_bound;
                int pos = findNext(start + left_bound, nxt);

                while (pos <= right) {
                    int delta = pos - start - c;
                    ans[pos] = rem - delta * delta + 1;
                    nxt[pos] = findNext(pos + 1, nxt);
                    pos = nxt[pos];
                }
            }
        }

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < M; ++c) {
                if (c) cout << ' ';
                cout << ans[r * M + c];
            }
            cout << '\n';
        }
    }
    return 0;
}
