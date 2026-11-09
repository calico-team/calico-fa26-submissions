#include <bits/stdc++.h>
using namespace std;

static int N, M;
static vector<string> g;
static vector<int> ar, ac, br, bc, kk, best;
static const int INF = 1000000007;

static inline bool act(int r, int c, int m) {
    char ch = g[r][c];
    if (ch == '.') return true;
    if (ch == 'B') return m == 0;
    return m == 1;
}

static void solve(int l, int r, const vector<int>& qs) {
    if (qs.empty()) return;
    int mid = (l + r) / 2;
    int W = r - l + 1;
    int S = W * N * 2;
    vector<int> dist(S), que(S);
    static const int dr[4] = {1, -1, 0, 0};
    static const int dc[4] = {0, 0, 1, -1};
    for (int sr = 0; sr < N; sr++) {
        for (int sm = 0; sm < 2; sm++) {
            if (!act(sr, mid, sm)) continue;
            fill(dist.begin(), dist.end(), -1);
            int head = 0, tail = 0;
            int s = (((mid - l) * N + sr) << 1) | sm;
            dist[s] = 0;
            que[tail++] = s;
            while (head < tail) {
                int id = que[head++];
                int m = id & 1;
                int t = id >> 1;
                int row = t % N;
                int col = t / N + l;
                int d = dist[id];
                for (int k = 0; k < 4; k++) {
                    int nr = row + dr[k], nc = col + dc[k];
                    if (nr < 0 || nr >= N || nc < l || nc > r) continue;
                    if (!act(nr, nc, m)) continue;
                    int nid = (((nc - l) * N + nr) << 1) | m;
                    if (dist[nid] < 0) {
                        dist[nid] = d + 1;
                        que[tail++] = nid;
                    }
                }
                if (g[row][col] == '.') {
                    int nid = id ^ 1;
                    if (dist[nid] < 0) {
                        dist[nid] = d + 1;
                        que[tail++] = nid;
                    }
                }
            }
            for (int q : qs) {
                int ia = (((ac[q] - l) * N + ar[q]) << 1);
                int da = dist[ia];
                if (da < 0) continue;
                int ib = (((bc[q] - l) * N + br[q]) << 1);
                int d0 = dist[ib], d1 = dist[ib | 1];
                if (d0 >= 0 && da + d0 < best[q]) best[q] = da + d0;
                if (d1 >= 0 && da + d1 < best[q]) best[q] = da + d1;
            }
        }
    }
    if (l == r) return;
    vector<int> left, right;
    for (int q : qs) {
        if (ac[q] <= mid && bc[q] <= mid) left.push_back(q);
        else if (ac[q] > mid && bc[q] > mid) right.push_back(q);
    }
    solve(l, mid, left);
    solve(mid + 1, r, right);
}

int main() {
    int T;
    if (scanf("%d", &T) != 1) return 0;
    string out;
    char row[4100];
    while (T--) {
        int Q;
        scanf("%d %d %d", &N, &M, &Q);
        g.assign(N, string());
        for (int i = 0; i < N; i++) {
            scanf("%s", row);
            g[i] = row;
        }
        ar.assign(Q, 0);
        ac.assign(Q, 0);
        br.assign(Q, 0);
        bc.assign(Q, 0);
        kk.assign(Q, 0);
        best.assign(Q, INF);
        vector<int> qs(Q);
        for (int i = 0; i < Q; i++) {
            scanf("%d %d %d %d %d", &ar[i], &ac[i], &br[i], &bc[i], &kk[i]);
            qs[i] = i;
            if (ar[i] == br[i] && ac[i] == bc[i]) best[i] = 0;
        }
        solve(0, M - 1, qs);
        for (int i = 0; i < Q; i++) {
            out += (best[i] <= kk[i]) ? "YES\n" : "NO\n";
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}