#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <numeric>
#include <climits>
#include <string>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<vector<char>> board(n, vector<char>(m));
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                board[i][j] = s[j];
            }
        }

        vector<vector<int>> visited(n, vector<int>(m, 0));
        int counter = 1;

        auto dfs = [&](auto&& self, int x, int y)-> void {
            visited[x][y] = counter;
            if ((x + 1) < n && visited[x + 1][y] == 0 && (board[x][y] == '.' || board[x + 1][y] == '.' || board[x][y] == board[x + 1][y])) {

                self(self, x + 1, y);
            }

            if ((x - 1) >= 0 && visited[x - 1][y] == 0 && (board[x][y] == '.' || board[x - 1][y] == '.' || board[x][y] == board[x - 1][y])) {
                self(self, x - 1, y);
            }

            if ((y + 1) < m && visited[x][y + 1] == 0 && (board[x][y] == '.' || board[x][y + 1] == '.' || board[x][y] == board[x][y + 1])) {
                self(self, x, y + 1);
            }

            if ((y - 1) >= 0 && visited[x][y - 1] == 0 && (board[x][y] == '.' || board[x][y - 1] == '.' || board[x][y] == board[x][y - 1])) {
                self(self, x, y - 1);
            }
        };


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visited[i][j] == 0) {
                    dfs(dfs, i, j);
                    counter++;
                }
            }
        }


        for (int i = 0; i < q; i++) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (visited[x1][y1] == visited[x2][y2]) {
                cout << "YES" << "\n";
            } else {
                cout << "NO" << "\n";
            }
        }

    }


}