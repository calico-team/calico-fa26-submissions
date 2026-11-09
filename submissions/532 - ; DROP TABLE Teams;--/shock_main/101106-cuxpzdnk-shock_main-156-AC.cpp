#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int free(vector<pair<int,int>>& row, int c) {
    int f = c;
    while (row[f].second != f) {
        f = row[f].second;
    }
    while (row[c].second != f && c != f) {
        int jump = row[c].second;
        row[c].second = f;
        c = jump;
    }
    return f;
}

void quake(vector<vector<pair<int,int>>>& squares, int R, int C, int P) {
    for (int r = R-P; r <= R+P; r++) {
        int vert = r-R;
        int rem = P*P - vert*vert;
        int w = sqrt(rem);
        while (w*w > rem) {
            w--;
        }
        while ((w+1)*(w+1) <= rem) {
            w++;
        }
        int c = free(squares[r], C-w);
        while (c <= C+w) {
            int horiz = c-C;
            squares[r][c].first = rem-horiz * horiz+1;
            squares[r][c].second = c+1;
            c = free(squares[r], c+1);
        }
    }
}
void solve() {
    int n,m,q; cin >> n >> m >> q;
    vector<vector<int>> quakes;
    for (int i = 0; i < q; i++) {
        int r,c,p; cin >> r >> c >> p;
        quakes.push_back({r,c,p});
    }
    vector<vector<pair<int,int>>> squares(n,vector<pair<int,int>>(m+1));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c <= m; c++) {
            squares[r][c] = {0,c};
        }
    }
    for (int i = q-1; i >= 0; i--) {
        quake(squares, quakes[i][0], quakes[i][1], quakes[i][2]);
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cout << squares[r][c].first;
            if (c < m - 1) cout << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}