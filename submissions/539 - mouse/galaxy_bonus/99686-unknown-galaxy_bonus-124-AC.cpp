#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector <vector <char>> color(n, vector <char>(m));
        for (auto &i : color) {
            for (auto &j : i) {
                cin >> j;
            }
        }
        vector <vector <int>> type(n, vector <int>(m, -1));
        int num = 0;
        function <void(int, int, int)> floodfill = [&](int r, int c, int ty) {
            if (r < 0 || r >= n || c < 0 || c >= m || type[r][c] != -1) {
                return;
            }
            char cc = color[r][c];
            type[r][c] = ty;
            if (cc == '.') {
                floodfill(r+1, c, ty);
                floodfill(r-1, c, ty);
                floodfill(r, c+1, ty);
                floodfill(r, c-1, ty);
            }
            else {
                array <int, 4> addR {1, 0, -1, 0}, addC {0, 1, 0, -1};
                for (int i = 0; i < 4; i++) {
                    int row = r+addR[i], col = c+addC[i];
                    if (row < 0 || row >= n || col < 0 || col >= m) {
                        continue;
                    }
                    if (color[row][col] == cc || color[row][col] == '.') {
                        floodfill(row, col, ty);
                    }
                }
            }
        };
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (type[i][j] == -1) {
                    floodfill(i, j, num);
                    num++;
                }
            }
        }
        while (q--) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            if (type[r1][c1] == type[r2][c2]) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
}