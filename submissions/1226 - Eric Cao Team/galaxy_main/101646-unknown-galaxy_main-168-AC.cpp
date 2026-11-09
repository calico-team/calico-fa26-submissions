#include <bits/stdc++.h>
using namespace std;
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    vector<vector<int>> component(N, vector<int>(M, -1));
    vector<int> row = {1, -1, 0, 0};
    vector<int> col = {0, 0, 1, -1};
    int count = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (component[i][j] != -1) continue;
            queue<pair<int, int>> q;
            q.push({i, j});
            component[i][j] = count;
            while (!q.empty()){
                auto[x, y] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++){
                    int neighbourx = x + row[k];
                    int neighboury = y + col[k];
                    if (neighbourx < 0 || neighbourx >= N || neighboury < 0 || neighboury >= M){
                        continue;
                    }
                    if (component[neighbourx][neighboury] != -1){
                        continue;
                    }
                    if (G[x][y] != '.' && G[neighbourx][neighboury] != '.' && G[x][y] != G[neighbourx][neighboury]){
                        continue;
                    }
                    component[neighbourx][neighboury] = count;
                    q.push({neighbourx, neighboury});
                }
            }
            count++;
        }
    }
    vector<string> answer;
    for (int i = 0; i < Q; i++){
        auto [x, y] = start[i];
        auto [neighbourx, neighboury] = end[i];
        if (component[x][y] == component[neighbourx][neighboury]){
            answer.push_back("YES");
        } else {
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
