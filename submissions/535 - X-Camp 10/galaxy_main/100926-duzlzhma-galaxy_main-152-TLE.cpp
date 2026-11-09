#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
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
struct state {
    int row;
    int col;
    int mode;
};

void flip(int row, int col, int mode, vector<string>& G, vector<vector<bool>>& blue,
    vector<vector<bool>>& red, queue<state>& q) {
    if (G[row][col] != '.') {
        return;
    }
    if (mode == 1) {
        if (!blue[row][col]) {
            blue[row][col] = true;
            q.push({ row, col, 0 });
        }
    }
    else {

        if (!red[row][col]) {
            red[row][col] = true;
            q.push({ row, col, 1 });
        }
    }
}
bool issolid(char tile, int mode) {
    if (mode == 1) {
        if (tile == 'R') {
            return true;
        }
    }
    if (mode == 0) {
        if (tile == 'B') {
            return true;
        }
    }
    if (tile == '.') {
        return true;
    }
    return false;
}

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    // YOUR CODE HERE
    vector<string> ans;
    for (int i = 0; i < Q; i++) {
        int fx = end[i].first;
        int fy = end[i].second;
        vector<vector<bool>> blue(N, vector<bool>(M, false)); //blue map
        vector<vector<bool>> red(N, vector<bool>(M, false)); //redmap
        queue<state> q;

        if (issolid(G[fx][fy], 0)) {
            blue[fx][fy] = true;
            q.push({ fx, fy, 0 });
        }
        if (issolid(G[fx][fy], 1)) {
            red[fx][fy] = true;
            q.push({ fx, fy, 1 });
        }
        int move[4] = { -1,1,-1,1 }; //goes uo,down,left,right

        while (!q.empty()) {
            state cur = q.front();
            q.pop();
            int ro = cur.row;
            int co = cur.col;
            int mo = cur.mode;

            for (int i = 0; i < 4; i++) {
                int a = ro; //row change
                int b = co;//col cahnge
                if (i < 2) {//up or down
                    a = ro + move[i];
                }
                else {
                    b = co + move[i];
                }
                if (a < 0 or a >= N or b < 0 or b >= M) {
                    continue;
                }
                if (!issolid(G[a][b], mo)) {
                    continue;
                }
                if (mo == 0) {
                    if (blue[a][b]) {//blue check
                        continue;
                    }
                    blue[a][b] = true;
                }
                else {
                    if (red[a][b]) {//blue check
                        continue;
                    }
                    red[a][b] = true;
                }
                q.push({ a,b,mo });
            }
            flip(ro, co, mo, G, blue, red, q);
        }
        if (blue[start[i].first][start[i].second]) {
            ans.push_back("YES");
        }
        else {
            ans.push_back("NO");
        }
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
        for (int j = 0; j < N; j++) {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++) {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({ start_row, start_col });
            end.push_back({ end_row, end_col });
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
}
