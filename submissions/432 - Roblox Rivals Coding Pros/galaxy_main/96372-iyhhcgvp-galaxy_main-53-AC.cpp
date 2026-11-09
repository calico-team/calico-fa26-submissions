#include "bits/stdc++.h"

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

constexpr int mm = 2e5 + 3;

int n, m, q;
pii dsu[205][205]{};
string g[205];

pii root(int r, int c) {
    auto [pr, pc] = dsu[r][c];
    if (pr == r && pc == c) return {r, c};
    dsu[r][c] = root(pr, pc);
    return dsu[r][c];
}

void merge(int r1, int c1, int r2, int c2) {
    pii root1 = root(r1, c1);
    pii root2 = root(r2, c2);
    if (root1 == root2) return;
    dsu[root1.first][root1.second] = root2;
}

void merge_helper(int r1, int c1, int r2, int c2) {
    if (r2 < 0 || r2 >= n || c2 < 0 || c2 >= m) return;
    if (g[r1][c1] != g[r2][c2] && g[r1][c1] != '.' && g[r2][c2] != '.') return;
    merge(r1, c1, r2, c2);
}

void solve() {
    cin >> n >> m >> q;
    
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dsu[i][j] = {i, j};
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            merge_helper(i, j, i+1, j);
            merge_helper(i, j, i-1, j);
            merge_helper(i, j, i, j+1);
            merge_helper(i, j, i, j-1);
        }
    }
    
    while (q--) {
        int rb, cb, re, ce;
        cin >> rb >> cb >> re >> ce;
        if (root(rb, cb) == root(re, ce)) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
} 
