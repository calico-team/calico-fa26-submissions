#include <bits/stdc++.h>

using namespace std;

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the G
 * M: the number of columns in the G
 * Q: the number of queries
 * G: the G, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */
vector<vector<bool>> visited;
int N, M, Q;

vector<string> G;

void BFS(int posX, int posY){
    if (visited[posX][posY]){
        return;
    }

    visited[posX][posY] = true;
    if (posX > 0){
        if (G[posX][posY] == '.' || G[posX-1][posY] == '.' || G[posX-1][posY] == G[posX][posY]){
            BFS(posX-1, posY);
        }
    }
    if (posY > 0){
        if (G[posX][posY] == '.' || G[posX][posY-1] == '.' || G[posX][posY-1] == G[posX][posY]){
            BFS(posX, posY-1);
        }
    }
    if (posX < M-1){
        if (G[posX][posY] == '.' || G[posX+1][posY] == '.' || G[posX+1][posY] == G[posX][posY]){
            BFS(posX+1, posY);
        }
    }
    if (posY < N-1){
        if (G[posX][posY] == '.' || G[posX][posY+1] == '.' || G[posY+1][posY] == G[posX][posY]){
            BFS(posX, posY+1);
        }
    }
    
}
 vector<string> solve(int N, int M, int Q, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // YOUR CODE HERE
    visited.assign(N, vector<bool>(M, false));
    BFS(N-1, M-1);
    vector<string> answer;
    for (int i = 0; i < Q; i++){
        if (visited[start[i].first][start[i].second]){
            answer.push_back("YES");
        }
        else{
            answer.push_back("NO");
        }
    }

    return answer;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, M, Q;
        cin >> N >> M >> Q;
        G.assign(N, "");

        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        G[N-1][M-1] = '.';
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, start, end)) {
            cout << s << '\n';
        }
    }
}
