#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M, Q;
        scanf("%d %d %d", &N, &M, &Q);
        vector<int> X(Q), Y(Q), P(Q);
        for (int i = 0; i < Q; i++) scanf("%d %d %d", &X[i], &Y[i], &P[i]);
        vector<int> grid((size_t)N * M, 0);
        vector<int> nxt((size_t)N * (M + 1));
        for (int r = 0; r < N; r++)
            for (int c = 0; c <= M; c++) nxt[(size_t)r * (M + 1) + c] = c;
        for (int i = Q - 1; i >= 0; i--) {
            long long PP = (long long)P[i] * P[i];
            for (int r = max(0, X[i] - P[i]); r <= min(N - 1, X[i] + P[i]); r++) {
                long long dr = r - X[i];
                long long v = PP - dr * dr;
                long long w = (long long)sqrtl((long double)v);
                while (w * w > v) w--;
                while ((w + 1) * (w + 1) <= v) w++;
                int lo = max(0LL, Y[i] - w);
                int hi = min((long long)M - 1, Y[i] + w);
                int* nr = &nxt[(size_t)r * (M + 1)];
                int* row = &grid[(size_t)r * M];
                int c = lo;
                while (true) {
                    int root = c;
                    while (nr[root] != root) root = nr[root];
                    while (nr[c] != root) {
                        int t = nr[c];
                        nr[c] = root;
                        c = t;
                    }
                    c = root;
                    if (c > hi) break;
                    long long dc = c - Y[i];
                    row[c] = (int)(v + 1 - dc * dc);
                    nr[c] = c + 1;
                    c++;
                }
            }
        }
        string out;
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                if (c) out += ' ';
                out += to_string(grid[(size_t)r * M + c]);
            }
            out += '\n';
        }
        fputs(out.c_str(), stdout);
    }
    return 0;
}
 