#include "bits/stdc++.h"

using namespace std;

#define int long long

const int N = 2e5 + 10;
const int md = 1e9 + 7;
const int INF = 1e18;

struct xxx {

    int x, y;
    char tp;

};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<vector<char>> a(n, vector<char> (m));
        vector<pair<int, int>> ps;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                if (a[i][j] == '.')
                    ps.push_back({i, j});
            }

        
        queue<xxx> qe;
        vector<vector<int>> num(n, vector<int> (m, -1));
        int cnt = 0;
        for (auto i : ps) {
            if (num[i.first][i.second] == -1) {
                num[i.first][i.second] = cnt++;
                qe.push({i.first, i.second, 'R'});
                qe.push({i.first, i.second, 'B'});
            }
            while (!qe.empty()) {
                int x = qe.front().x;
                int y = qe.front().y;
                char tp = qe.front().tp;
                qe.pop();
                for (int d1 = -1; d1 <= 1; d1++)
                    for (int d2 = -1; d2 <= 1; d2++)
                        if ((abs(d1) + abs(d2)) == 1) {
                            if ((x + d1) >= 0 && (x + d1) < n && (y + d2) >= 0 && (y + d2) < m) {
                                if (a[x + d1][y + d2] == tp && num[x + d1][y + d2] == -1) {
                                    num[x + d1][y + d2] = cnt - 1;
                                    qe.push({x + d1, y + d2, tp});
                                }
                                if (a[x + d1][y + d2] == '.' && num[x + d1][y + d2] == -1) {
                                    num[x + d1][y + d2] = cnt - 1;
                                    qe.push({x + d1, y + d2, 'R'});
                                    qe.push({x + d1, y + d2, 'B'});
                                }
                            }
                        }
            }
        }

        while (q--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if (num[x1][y1] == num[x2][y2])
                cout << "YES" << '\n';
            else cout << "NO" << '\n';
        }
    }

    return 0;
}