#include <iostream>
#include <vector>
#include <string>
#include <cstring>

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
string inp[300];
string G[300][300];
int visited[300][300][2];
int N, M;


bool isValid(int x, int y, int layer) {
    if (layer == 0) {
        return G[x][y] != "B";
    }

    if (layer == 1) {
        return G[x][y] != "R";
    }
    return false;
}

int dfs(int x, int y, int layer, int id) {

    visited[x][y][layer] = id;

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         cout << G[i][j];
    //     }
    //     cout << "\n";
    // }
    // cout << "\n\n";

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         cout << visited[i][j][1];
    //     }
    //     cout << "\n";
    // }
    // cout << "\n\n";

    
    if (x - 1 >= 0 && visited[x - 1][y][layer] == -1) {
        if (isValid(x - 1, y, layer)) {
            dfs(x - 1, y, layer, id);
        }
        

    }
    
    if (x + 1 < N && visited[x + 1][y][layer] == -1) {
        if (layer == 0 && G[x + 1][y] != "B") {
            dfs(x + 1, y, layer, id);
        }
        
        if (layer == 1 && G[x + 1][y] != "R") {
            dfs(x + 1, y, layer, id);
        }
        
    }
    
    if (y - 1 >= 0 && visited[x][y - 1][layer] == -1) {
        if (layer == 0 && G[x][y - 1] != "B") {
            dfs(x, y - 1, layer, id);
        }
        if (layer == 1 && G[x][y - 1] != "R") {
            dfs(x, y - 1, layer, id);
        }
    }
    
    if (y + 1 < M && visited[x][y + 1][layer] == -1) {
        
        if (layer == 0 && G[x][y + 1] != "B") {
            dfs(x, y + 1, layer, id);
        }
        
        if (layer == 1 && G[x][y + 1] != "R") {
            dfs(x, y + 1, layer, id);
        }
    }
    
    if (layer == 0 && visited[x][y][1] == -1 && G[x][y] == ".") {
        dfs(x, y, 1, id);
    }
    
    if (layer == 1 && visited[x][y][0] == -1 && G[x][y] == ".") {
        dfs(x, y, 0, id);
    }
    

    return 1;
    
}
 
 
vector<string> solve(int a, int b, int Q, auto B, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {

    // fill(&visited[0][0][0], &visited[0][0][0] + (N*M*Q), -1);
    memset(visited, -1, sizeof(visited));
    vector<string> testcases;
    int id = 0;
    bool det = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 2; k++) {
                if (visited[i][j][k] == -1 && isValid(i, j, k)) {
                    dfs(i, j, k, id);
                    id++;
                }
            }

        }

    }
    for (int loopvariable = 0; loopvariable < Q; loopvariable++) {
        
        int startX = start[loopvariable].first;
        int startY = start[loopvariable].second;
        int endX = end[loopvariable].first;
        int endY = end[loopvariable].second;
        
        // cout << verify;
        if (visited[startX][startY][1] == visited[endX][endY][1]) {
            testcases.push_back("YES");
        } else {
            testcases.push_back("NO");
        }
        
    }
    return testcases;
}

int main() {

    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int Q;
        cin >> N >> M >> Q;
        for (int j = 0; j < N; j++) {
            cin >> inp[j];

            for (int k = 0; k < M; k++) {
                G[j][k] = inp[j][k];
            }
            
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

