#include <bits/stdc++.h>
using namespace std;
struct Earthquake {
    int r, c, p;
};
vector<int> parent;
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<Earthquake> a(Q);
        for (int i = 0; i < Q; i++) {
            cin >> a[i].r >> a[i].c >> a[i].p;
        }
        vector<vector<long long>> ans(
            N, vector<long long>(M, 0)
        );
        int H = min(N, M);
        int W = max(N, M);
        int len = W + 1;
        parent.resize(H * len);
        for (int i = 0; i < H * len; i++) {
            parent[i] = i;
        }
        for (int i = Q - 1; i >= 0; i--) {
            int r = (N <= M ? a[i].r : a[i].c);
            int c = (N <= M ? a[i].c : a[i].r);
            int p = a[i].p;
            long long pp = 1LL * p * p;
            for (int d = -p; d <= p; d++) {
                int row = r + d;
                long long rem = pp - 1LL * d * d;
                int dx = sqrtl(rem);
                while (1LL * (dx + 1) * (dx + 1) <= rem)
                    dx++;
                while (1LL * dx * dx > rem)
                    dx--;
                int L = max(0, c - dx);
                int R = min(W - 1, c + dx);
                int cur = find(row * len + L);
                while (cur % len <= R) {
                    int col = cur % len;
                    long long value =
                        rem - 1LL * (col - c) * (col - c) + 1;
                    if (N <= M)
                        ans[row][col] = value;
                    else
                        ans[col][row] = value;
                    parent[cur] = find(cur + 1);
                    cur = find(cur);
                }
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j) cout << " ";
                cout << ans[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}