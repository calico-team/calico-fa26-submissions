#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
int R[20005], C[20005], P[20005];
int ans[1000005];
int nxt[2000005]; // N*(M+1), every row gets an extra column at the end as a stopper

// nxt[x] = x means block x isnt written yet. once its written point it at x+1 so find
// skips the whole run. not recursive because a run in one row can be like 1e5 long
int find(int x) {
    int r = x;
    while (nxt[r] != r) r = nxt[r];
    while (nxt[x] != r) { int y = nxt[x]; nxt[x] = r; x = y; }
    return r;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &N, &M, &Q);
        for (int i = 0; i < Q; i++) scanf("%d %d %d", &R[i], &C[i], &P[i]);
        for (int i = 0; i < N * M; i++) ans[i] = 0;
        for (int i = 0; i < N * (M + 1); i++) nxt[i] = i;

        // a block only keeps the last quake that hit it, so go backwards and the first quake
        // to reach a block wins. every block gets written once, and a quake only costs its
        // 2P+1 rows which is at most min(N,M) <= 1000, so 2e4 quakes is fine
        for (int i = Q - 1; i >= 0; i--) {
            int p = P[i], pp = p * p;
            for (int dr = -p; dr <= p; dr++) {
                // biggest w with dr^2 + w^2 <= p^2, this row of the circle is [C-w, C+w]
                int w = sqrt(pp - dr * dr);
                while (w * w + dr * dr > pp) w--;
                while ((w + 1) * (w + 1) + dr * dr <= pp) w++;

                int r = R[i] + dr, base = r * (M + 1);
                for (int x = find(base + C[i] - w); x - base <= C[i] + w; x = find(x + 1)) {
                    int c = x - base, dc = c - C[i];
                    ans[r * M + c] = pp - dr * dr - dc * dc + 1;
                    nxt[x] = x + 1;
                }
            }
        }

        for (int r = 0; r < N; r++)
            for (int c = 0; c < M; c++)
                printf("%d%c", ans[r * M + c], c + 1 == M ? '\n' : ' ');
    }
}
