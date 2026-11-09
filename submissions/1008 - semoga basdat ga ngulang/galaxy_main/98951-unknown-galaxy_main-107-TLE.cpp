
#include <bits/stdc++.h>
using namespace std;

#define ll long long

string mymap[205];
bool visited[205][205][2];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll t;
    cin >> t;

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        for (int i = 0; i < n; i++) {
            cin >> mymap[i];
        }

        while (k--) {
            int nstart, mstart, nend, mend;
            cin >> nstart >> mstart >> nend >> mend;

            memset(visited, 0, sizeof(visited));

            queue<tuple<int,int,int>> q;

            q.push({nstart, mstart, 0});
            visited[nstart][mstart][0] = true;

            bool ans = false;

            while (!q.empty()) {
                auto [y, x, mode] = q.front();
                q.pop();

                if (y == nend && x == mend) {
                    ans = true;
                    break;
                }

                for (int i = 0; i < 4; i++) {
                    int ty = y + dy[i];
                    int tx = x + dx[i];

                    if (ty < 0 || ty >= n || tx < 0 || tx >= m) continue;

                    if (mode == 0 && mymap[ty][tx] == 'R') continue;
                    if (mode == 1 && mymap[ty][tx] == 'B') continue;

                    if (visited[ty][tx][mode]) continue;

                    visited[ty][tx][mode] = true;
                    q.push({ty, tx, mode});
                }

                if (mymap[y][x] == '.') {
                    int newmode = 1 - mode;

                    if (!visited[y][x][newmode]) {
                        visited[y][x][newmode] = true;
                        q.push({y, x, newmode});
                    }
                }
            }

            cout << (ans ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
