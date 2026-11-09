#include <bits/stdc++.h>

using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i] within K[i]
 * seconds, and "NO" otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 * K: the maximum number of seconds allowed for each query
 */

void dfs(int y, int x, int n, int m, vector<vector<pair<int,int>>> &visits, vector<string> &builder, char last_visit, int distance, char last_colour) {
    if (visits[y][x].first == 1) return;

    if (last_visit != '.') {
        if (last_visit != builder[y][x] && builder[y][x] != '.') return;
    }

    visits[y][x].first = 1;
    visits[y][x].second = distance;

    char colour;
    int xx = 0;

    if (builder[y][x] != '.') {
        colour = builder[y][x];
    } else {
        if (builder[y][x] != last_colour) xx = 1;
        colour = last_colour;
    }
    
    if (x > 0) {
        dfs(y,x-1, n, m, visits, builder,builder[y][x], distance + 1 + xx, colour);
    }
    if (y > 0) {
        dfs(y-1,x,n,m,visits,builder,builder[y][x], distance + 1 + xx, colour);
    }
    if (x < m-1) {
        dfs(y,x+1,n,m,visits,builder,builder[y][x], distance + 1 + xx, colour);
    }
    if (y < n-1) {
        dfs(y+1,x,n,m,visits,builder,builder[y][x], distance + 1 + xx, colour);
    }
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    // YOUR CODE HERE

    for (int i=0;i<Q;i++) {
        vector<vector<pair<int,int>>> visits(N, vector<pair<int,int>>(M));
        dfs(end[i].first, end[i].second, N, M, visits, G, '.', 0, 'B');

        if (visits[start[i].first][start[i].second].first == 1 && visits[start[i].first][start[i].second].second <= K[i]) {
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
        vector<int> K;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col, k;
            cin >> start_row >> start_col >> end_row >> end_col >> k;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
            K.push_back(k);
        }

        for (string s : solve(N, M, Q, G, start, end, K)) {
            cout << s << '\n';
        }
    }
}
