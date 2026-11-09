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



vector<vector<bool>> visited;
vector<vector<int>> connected;
vector<string> graph;
int ctr = 1;
void dfs(int a, int b, int n, int m){
    if (visited[a][b]) return;
    visited[a][b] = 1;
    connected[a][b] = ctr;
    if (a != n-1){
        if (graph[a][b] == '.' or graph[a+1][b] == '.' or graph[a][b] == graph[a+1][b]){
            dfs(a+1,b,n,m);
        }
    }
    if (a != 0){
        if (graph[a][b] == '.' or graph[a-1][b] == '.' or graph[a][b] == graph[a-1][b]){
            dfs(a-1,b,n,m);
        }
    }
    if (b != m-1){
        if (graph[a][b] == '.' or graph[a][b+1] == '.' or graph[a][b] == graph[a][b+1]){
            dfs(a,b+1,n,m);
        }
    }
    if (b != 0){
        if (graph[a][b] == '.' or graph[a][b-1] == '.' or graph[a][b] == graph[a][b-1]){
            dfs(a,b-1,n,m);
        }
    }
}

vector<string> solve(int n, int m, int q, vector<string>& g, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    graph = g;
    visited = vector<vector<bool>> (n, vector<bool>(m));
    connected = vector<vector<int>> (n, vector<int>(m));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (!visited[i][j]){
                dfs(i,j,n,m);
                ctr += 1;
            }
        }
    }
    vector<string> ans;
    for (int i = 0; i < q; i++){
        pair<int,int> s = start[i];
        pair<int,int> e = end[i];
        ans.push_back((connected[s.first][s.second] == connected[e.first][e.second]? "YES":"NO"));
    }
    return ans;
}

int main() {
    //freopen("00_main.in","r",stdin);
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
