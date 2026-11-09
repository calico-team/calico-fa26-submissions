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

void dfs(int y, int x, int n, int m, vector<vector<int>> &visits, vector<string> &builder, char last_visit) {
    if (visits[y][x] == 1) return;

    if (last_visit != '.') {
        if (last_visit != builder[y][x]) return;
    }

    visits[y][x] = 1;
    
    if (x > 0) {
        if (builder[y][x-1] == '.') dfs(y,x-1, n, m, visits, builder,builder[y][x]);
    }
    if (y > 0) {
        if (builder[y-1][x] == '.') dfs(y-1,x,n,m,visits,builder,builder[y][x]);
    }
    if (x < m-1) {
        if (builder[y][x+1] == '.') dfs(y,x+1,n,m,visits,builder,builder[y][x]);
    }
    if (y < n-1) {
        if (builder[y+1][x] == '.') dfs(y+1,x,n,m,visits,builder,builder[y][x]);
    }
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // YOUR CODE HERE
    vector<vector<int>> visits(N, vector<int>(M));
    dfs(N-1, M-1, N, M, visits, G, '.');

    for (auto i : start) {
        if (visits[i.first][i.second] == 1) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }

    return {};
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
}
