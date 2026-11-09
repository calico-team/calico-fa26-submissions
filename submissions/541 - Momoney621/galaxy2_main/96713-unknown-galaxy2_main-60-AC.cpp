#include <bits/stdc++.h>

using namespace std;

const int UNREACHABLE = INT_MAX / 2;
const int ROW_STEP[] = {1, -1, 0, 0};
const int COL_STEP[] = {0, 0, 1, -1};

vector<string> solve(int N, int M, int Q, vector<string>& G, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    vector<int> best(Q, UNREACHABLE);

    function<void(int, int, vector<int>)> divide = [&](int lo, int hi, vector<int> queries) {
        if (lo > hi || queries.empty()) return;
        int mid = (lo + hi) / 2;
        int width = hi - lo + 1;
        auto state = [&](int r, int c, int m) {
            return ((r * width) + (c - lo)) * 2 + m;
        };
        auto active = [&](int r, int c, int m) {
            char cell = G[r][c];
            return cell == '.' || cell == "BR"[m];
        };

        int stride = 2 * N;
        vector<int> dist(N * width * 2 * stride, UNREACHABLE);
        int sources = 0;
        for (int row = 0; row < N; row++) {
            for (int mode = 0; mode < 2; mode++) {
                if (!active(row, mid, mode)) continue;
                vector<int> d(N * width * 2, UNREACHABLE);
                vector<int> frontier = {state(row, mid, mode)};
                d[frontier[0]] = 0;
                for (size_t head = 0; head < frontier.size(); head++) {
                    int from = frontier[head];
                    int r = from / 2 / width;
                    int c = lo + from / 2 % width;
                    int m = from % 2;
                    auto visit = [&](int to) {
                        if (d[to] != UNREACHABLE) return;
                        d[to] = d[from] + 1;
                        frontier.push_back(to);
                    };
                    for (int k = 0; k < 4; k++) {
                        int r2 = r + ROW_STEP[k], c2 = c + COL_STEP[k];
                        if (r2 < 0 || r2 >= N || c2 < lo || c2 > hi || !active(r2, c2, m)) continue;
                        visit(state(r2, c2, m));
                    }
                    if (G[r][c] == '.') visit(state(r, c, m ^ 1));
                }
                for (size_t to = 0; to < d.size(); to++) dist[to * stride + sources] = d[to];
                sources++;
            }
        }

        vector<int> left, right;
        for (int q : queries) {
            int* to_start = &dist[state(start[q].first, start[q].second, 0) * stride];
            int* to_end_blue = &dist[state(end[q].first, end[q].second, 0) * stride];
            int* to_end_red = &dist[state(end[q].first, end[q].second, 1) * stride];
            for (int i = 0; i < sources; i++) {
                int to_mid = to_start[i];
                int from_mid = min(to_end_blue[i], to_end_red[i]);
                if (to_mid < UNREACHABLE && from_mid < UNREACHABLE) best[q] = min(best[q], to_mid + from_mid);
            }
            int a = start[q].second, b = end[q].second;
            if (max(a, b) < mid) left.push_back(q);
            if (min(a, b) > mid) right.push_back(q);
        }
        divide(lo, mid - 1, left);
        divide(mid + 1, hi, right);
    };

    vector<int> all(Q);
    iota(all.begin(), all.end(), 0);
    divide(0, M - 1, all);

    vector<string> answers(Q);
    for (int q = 0; q < Q; q++){
        answers[q] = best[q] <= K[q] ? "YES" : "NO";
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
