#include <bits/stdc++.h>
using namespace std;

static int par[2100000];
static int val[1000005];

int findp(int base, int c) {
    int x = c;
    while (par[base + x] != x) x = par[base + x];
    while (par[base + c] != x) {
        int nx = par[base + c];
        par[base + c] = x;
        c = nx;
    }
    return x;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, q;
        scanf("%d %d %d", &n, &m, &q);
        vector<array<int,3>> E(q);
        for (auto &e : E) scanf("%d %d %d", &e[0], &e[1], &e[2]);

        int W = m + 1;
        for (int r = 0; r < n; r++)
            for (int c = 0; c <= m; c++) par[r * W + c] = c;
        for (int i = 0; i < n * m; i++) val[i] = 0;

        for (int i = q - 1; i >= 0; i--) {
            int R = E[i][0], C = E[i][1], P = E[i][2];
            for (int dr = -P; dr <= P; dr++) {
                int r = R + dr;
                int rem = P * P - dr * dr;
                int w = (int)sqrt((double)rem);
                while (w * w > rem) w--;
                while ((w + 1) * (w + 1) <= rem) w++;
                int lo = C - w, hi = C + w;
                int base = r * W;
                int c = findp(base, lo);
                while (c <= hi) {
                    int dc = c - C;
                    val[r * m + c] = rem - dc * dc + 1;
                    par[base + c] = c + 1;
                    c = findp(base, c + 1);
                }
            }
        }

        string out;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                out += to_string(val[r * m + c]);
                out += (c + 1 < m ? ' ' : '\n');
            }
        }
        fputs(out.c_str(), stdout);
    }
    return 0;
}