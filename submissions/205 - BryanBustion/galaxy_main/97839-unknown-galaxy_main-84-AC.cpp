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

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end) {
    int sz = N * M;
    vector<int> parent(sz), rank(sz, 0);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](int x) {
        int root = x;
        while (parent[root] != root)
            root = parent[root];
        while (parent[x] != x) {
            int p = parent[x];
            parent[x] = root;
            x = p;
        }
        return root;
    };
    auto unite = [&](int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    };
    auto id = [&](int r, int c) {
        return r * M + c;
    };
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            if (c + 1 < M) {
                char a = G[r][c];
                char b = G[r][c + 1];
                if (a == '.' || b == '.' || a == b) {
                    unite(id(r, c), id(r, c + 1));
                }
            }
            if (r + 1 < N) {
                char a = G[r][c];
                char b = G[r + 1][c];
                if (a == '.' || b == '.' || a == b) {
                    unite(id(r, c), id(r + 1, c));
                }
            }
        }
    }
    vector<string> ans;
    ans.reserve(Q);
    for (int i = 0; i < Q; i++) {
        int s = id(start[i].first, start[i].second);
        int e = id(end[i].first, end[i].second);
        if (find(s) == find(e))
            ans.push_back("YES");
        else
            ans.push_back("NO");
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
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end)) {
            cout << s << '\n';
        }
    }
}
