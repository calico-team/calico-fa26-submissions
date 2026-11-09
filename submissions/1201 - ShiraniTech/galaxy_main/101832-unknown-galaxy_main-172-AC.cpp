#include<iostream>
#include<string>
#include<vector>
using namespace std;
vector<int> par;

int findp(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]];
        x = par[x];
    }
    return x;
}

void unite(int a, int b) {
    a = findp(a);
    b = findp(b);
    if (a != b) par[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> g(n);
        for (auto& row : g) cin >> row;

        auto active = [&](int r, int c, int mode) {
            char ch = g[r][c];
            if (ch == '.') return true;
            if (ch == 'B') return mode == 0;
            return mode == 1; 
        };

    par.assign(n * m * 2, 0);
       for (int i = 0; i < n * m * 2; i++) par[i] = i;

for (int r = 0; r < n; r++) {
           for (int c = 0; c < m; c++) {
                if (g[r][c] == '.')
                  unite((r * m + c) * 2, (r * m + c) * 2 + 1);  
                for (int mode = 0; mode < 2; mode++) {
                    if (!active(r, c, mode)) continue;
                   if (r + 1 < n && active(r + 1, c, mode))
                        unite((r * m + c) * 2 + mode, ((r + 1) * m + c) * 2 + mode);
                    if (c + 1 < m && active(r, c + 1, mode))
                     unite((r * m + c) * 2 + mode, (r * m + c + 1) * 2 + mode);
                }
            }
        }
while (q--) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            int a = findp((rs * m + cs) * 2);  
            bool ok = false;
            for (int mode = 0; mode < 2; mode++) {
                if (active(re, ce, mode) &&
                    findp((re * m + ce) * 2 + mode) == a)
                    ok = true;
            }
            cout << (ok ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}