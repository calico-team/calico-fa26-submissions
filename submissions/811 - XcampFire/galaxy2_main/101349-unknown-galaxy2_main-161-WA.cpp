#include <iostream>
#include <string.h>
#include <queue>
#include <utility>
using namespace std;

struct Node {
    int r, c, time;
    char color;
};
char g[20][4010];
int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};
bool visited[20][4010][2];

bool solve(int n, int m, int r_start, int c_start, int r_end, int c_end, int k) {
    queue<Node> q;
    q.push({r_start, c_start, 0, 'B'});
    visited[r_start][c_start][0] = true;
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        if (curr.time > k) continue;
        if (curr.r == r_end && curr.c == c_end && curr.time <= k) return true;
        for (int i = 0; i < 4; i++) {
            int n_time = curr.time;
            char n_color = curr.color;
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (g[nr][nc] != '.' && g[nr][nc] != curr.color) {
                    if (g[curr.r][curr.c] == '.') {
                        n_time++;
                        n_color = g[nr][nc];
                    } else continue;
                }
                if (visited[nr][nc][n_color == 'B' ? 0 : 1]) continue;
                q.push({nr, nc, n_time + 1, n_color});
                visited[nr][nc][n_color == 'B' ? 0 : 1] = true;
            }
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m, q;
        cin >> n >> m >> q;
        for (int j = 0; j < n; j++) {
            cin >> g[j];
        }
        for (int j = 0; j < q; j++) {
            memset(visited, false, sizeof(visited));
            int r_start, r_end, c_start, c_end, k;
            cin >> r_start >> c_start >> r_end >> c_end >> k;
            bool ret = solve(n, m, r_start, c_start, r_end, c_end, k);
            if (ret) cout << "YES";
            else cout << "NO";
            cout << endl;
        }
    }
    return 0;
}