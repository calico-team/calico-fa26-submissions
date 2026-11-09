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

// state: 0 for blue, 1 for red
vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};
void bfs(vector<vector<int>>& visited, int N, int M, const vector<string>& G){
    queue<tuple<int, int, int>> q;

    q.push({N - 1, M - 1, 0});
    q.push({N - 1, M - 1, 1});
    visited[N - 1][M - 1] |= (1 << 0) | (1 << 1);

    while (!q.empty()){
        auto [current_i, current_j, state] = q.front();
        q.pop();
        if (G[current_i][current_j] == '.' && !(visited[current_i][current_j] & (1 << !state))){
            visited[current_i][current_j] |= (1 << !state);
            q.push({current_i, current_j, !state});
        }
        for (int i = 0; i < 4; i++) {
            int new_i = current_i - dx[i], new_j = current_j - dy[i];
            if (new_i >= 0 && new_i < N && new_j >= 0 && new_j < M) {
                if (!(visited[new_i][new_j] & (1 << state))){
                    if (G[new_i][new_j] == '.' || (G[new_i][new_j] == 'B' && state == 0) || (G[new_i][new_j] == 'R' && state == 1)){
                        if(!(visited[new_i][new_j] & (1 << state))){
                            visited[new_i][new_j] |= (1 << state);
                            q.push({new_i, new_j, state});
                        }
                    }
                    
                }
            }
        }
    }
}
void dfs(vector<vector<int>>& visited, int current_i, int current_j, bool state, int N, int M, const vector<string>& G) {
	if (visited[current_i][current_j] & (1 << state)) return;
	visited[current_i][current_j] |= (1 << state);
	for (int i = 0; i < 4; i++) {
        int new_i = current_i - dx[i], new_j = current_j - dy[i];
        if (new_i >= 0 && new_i < N && new_j >= 0 && new_j < M) {
            if (G[new_i][new_j] == '.' || (G[new_i][new_j] == 'B' && state == 0) || (G[new_i][new_j] == 'R' && state == 1)){
                dfs(visited, new_i, new_j, state, N, M, G);
            }
        }
    }
    if (G[current_i][current_j] == '.'){
        dfs(visited, current_i, current_j, !state, N, M, G);
    }
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // YOUR CODE HERE
    vector<string> r(Q);
    vector<vector<int>> v(N,vector<int>(M,0));
    bfs(v, N, M, G);
    for (int i = 0; i < Q; i++) {
        if (v[start[i].first][start[i].second] && (1 << 0)) r[i] = "YES";
        else r[i] = "NO";
    }
    return r;
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