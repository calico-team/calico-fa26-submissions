#include <bits/stdc++.h>
using namespace std;
/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */

int p[160005];

int find(int x) 
{
    if (p[x] == x)  return x;
    return p[x] = find(p[x]);
}

void unite(int x, int y) 
{
    int rx = find(x),ry = find(y);
    if (rx != ry)  p[rx] = ry;
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    vector<vector<int>> id0(N, vector<int>(M, -1));
    vector<vector<int>> id1(N, vector<int>(M, -1));
    int cc = 0;
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            if (G[i][j] == '.' || G[i][j] == 'B') id0[i][j] = cc++;
            if (G[i][j] == '.' || G[i][j] == 'R') id1[i][j] = cc++;
        }
    }
    for (int i = 0; i < cc; i++) p[i] = i;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < M; j++) 
        {
            if (G[i][j] == '.') unite(id0[i][j], id1[i][j]);
            for (int k = 0; k < 4; k++) 
            {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < N && nj >= 0 && nj < M) 
                {
                    if (id0[i][j] != -1 && id0[ni][nj] != -1) unite(id0[i][j], id0[ni][nj]);
                    if (id1[i][j] != -1 && id1[ni][nj] != -1) unite(id1[i][j], id1[ni][nj]);
                }
            }
        }
    }
    vector<string> ans;
    for (int i = 0; i < Q; i++) 
    {
        int sx = start[i].first;
        int sy = start[i].second;
        int ex = end[i].first;
        int ey = end[i].second;
        int s_idx = id0[sx][sy];
        int e0 = id0[ex][ey];
        int e1 = id1[ex][ey];
        bool ok = false;
        if (e0 != -1 && find(s_idx) == find(e0)) ok = true;
        if (e1 != -1 && find(s_idx) == find(e1)) ok = true;
        if (ok) ans.push_back("YES");
        else ans.push_back("NO");
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) cin >> G[j];
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }
        for (string s : solve(N, M, Q, G, start, end)) cout << s << '\n';
    }
}

