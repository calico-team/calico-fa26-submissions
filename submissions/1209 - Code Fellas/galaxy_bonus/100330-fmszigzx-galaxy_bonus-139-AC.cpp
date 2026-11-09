#include <bits/stdc++.h>
using namespace std;

vector<int> boss;

int getBoss(int x) {
    while (boss[x] != x) {
        boss[x] = boss[boss[x]];
        x = boss[x];
    }
    return x;
}

void merge(int a, int b) {
     a = getBoss(a);
     b = getBoss(b);
     if (a !=b) boss[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCount;
    cin>> testCount;
    while (testCount--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<string> board(n);
        for (int i = 0; i < n; i++) cin >> board[i];

        boss.resize(n * m *2);
        for (int i = 0; i < n * m * 2; i++) boss[i] = i;

        auto canStand = [&](int row, int col, int mode) {
            char title = board[row][col];
            if (title == '.') return true;
            if (title == 'B') return mode == 0;
            return mode == 1;
        };

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                int spot = row * m + col;

                if (board[row][col] == '.') merge(spot * 2, spot * 2 + 1);

                for (int mode = 0; mode < 2; mode++) {
                    if (!canStand(row, col, mode)) continue;

                    if (col + 1 < m && canStand(row, col + 1, mode))
                       merge(spot * 2 + mode, (spot + 1) * 2 + mode);
                    
                    if (row + 1 < n && canStand(row + 1, col, mode))
                       merge(spot * 2 + mode, (spot + m) * 2 + mode);
                }
            }
        }

        while (q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            int startGroup = getBoss((r1 * m + c1) * 2);
            int endSpot = r2 * m + c2;

            bool found = false;
            for  (int mode = 0; mode < 2; mode++) {
                if (canStand(r2, c2, mode) && getBoss(endSpot * 2 + mode) == startGroup) 
                found = true;
            } cout << (found ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}