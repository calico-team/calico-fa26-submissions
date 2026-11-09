#include <bits/stdc++.h>

using namespace std;


vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    vector<int> parent(2 * N * M);
    iota(parent.begin(), parent.end(), 0);
    auto root = [&](int x) {
        while (parent[x] != x) {
            x = parent[x] = parent[parent[x]];
        }
        return x;
    };
    auto active = [&](int r, int c, int mode) {
        return G[r][c] == '.' || G[r][c] == "BR"[mode];
    };
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            int tile = (r * M + c) * 2;
            for (int mode = 0; mode < 2; mode++) {
                if (!active(r, c, mode)) {
                    continue;
                }
                if (r + 1 < N && active(r + 1, c, mode)) {
                    parent[root(tile + mode)] = root(tile + 2 * M + mode);
                }
                if (c + 1 < M && active(r, c + 1, mode)) {
                    parent[root(tile + mode)] = root(tile + 2 + mode);
                }
            }
            if (G[r][c] == '.') {
                parent[root(tile)] = root(tile + 1);
            }
        }
    }
    vector<string> answers;
    for (int i = 0; i < Q; i++) {
        int from = (start[i].first * M + start[i].second) * 2;
        int to = (end[i].first * M + end[i].second) * 2 + (G[end[i].first][end[i].second] == 'R');
        answers.push_back(root(from) == root(to) ? "YES" : "NO");
    }
    return answers;
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
