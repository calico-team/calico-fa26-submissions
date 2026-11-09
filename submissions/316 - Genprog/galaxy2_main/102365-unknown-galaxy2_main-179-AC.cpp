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
vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    const long long BIG = 1LL << 60;
    vector<long long> shortest(Q, BIG);
    struct Job { int leftCol, rightCol; vector<int> ids; };
    vector<Job> todo;
    vector<int> all(Q);
    for (int i = 0; i < Q; i++) all[i] = i;
    todo.push_back({0, M - 1, all});
    vector<int> far, frontier;
    vector<char> open_, plain;
    while (!todo.empty()) {
        Job job = move(todo.back());
        todo.pop_back();
        int leftCol = job.leftCol, rightCol = job.rightCol;
        vector<int>& ids = job.ids;
        if (ids.empty() || leftCol > rightCol) continue;
        int w = rightCol - leftCol + 1, center = (leftCol + rightCol) / 2, area = N * w, S = area * 2;
        open_.assign(S, 0);
        plain.assign(area, 0);
        for (int r = 0; r < N; r++)
            for (int c = 0; c < w; c++) {
                char t = G[r][leftCol + c];
                int i = r * w + c;
                if (t == '.') { plain[i] = 1; open_[2 * i] = open_[2 * i + 1] = 1; }
                else if (t == 'R') open_[2 * i + 1] = 1;
                else open_[2 * i] = 1;
            }
        int step = 2 * w, cc = center - leftCol;
        far.resize(S);
        for (int r = 0; r < N; r++)
            for (int mode = 0; mode < 2; mode++) {
                int origin = (r * w + cc) * 2 + mode;
                if (!open_[origin]) continue;
                fill(far.begin(), far.end(), -1);
                far[origin] = 0;
                frontier.clear();
                frontier.push_back(origin);
                for (size_t h = 0; h < frontier.size(); h++) {
                    int x = frontier[h], nd = far[x] + 1, cell = x >> 1, c = cell % w;
                    int ys[5]; int k = 0;
                    if (c > 0) ys[k++] = x - 2;
                    if (c < w - 1) ys[k++] = x + 2;
                    if (x - step >= 0) ys[k++] = x - step;
                    if (x + step < S) ys[k++] = x + step;
                    for (int j = 0; j < k; j++) {
                        int y = ys[j];
                        if (open_[y] && far[y] < 0) { far[y] = nd; frontier.push_back(y); }
                    }
                    if (plain[cell]) {
                        int y = x ^ 1;
                        if (far[y] < 0) { far[y] = nd; frontier.push_back(y); }
                    }
                }
                for (int q : ids) {
                    int a = far[(start[q].first * w + start[q].second - leftCol) * 2];
                    if (a < 0) continue;
                    int e = (end[q].first * w + end[q].second - leftCol) * 2;
                    int b = far[e], b2 = far[e + 1];
                    if (b < 0 || (b2 >= 0 && b2 < b)) b = b2;
                    if (b < 0) continue;
                    if (a + b < shortest[q]) shortest[q] = a + b;
                }
            }
        vector<int> goL, goR;
        for (int q : ids) {
            int sc = start[q].second, ec = end[q].second;
            if (sc < center && ec < center) goL.push_back(q);
            else if (sc > center && ec > center) goR.push_back(q);
        }
        todo.push_back({leftCol, center - 1, move(goL)});
        todo.push_back({center + 1, rightCol, move(goR)});
    }
    vector<string> out(Q);
    for (int i = 0; i < Q; i++) out[i] = shortest[i] <= K[i] ? "YES" : "NO";
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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