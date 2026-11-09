#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int DR[] = {-1, 1, 0, 0};
    const int DC[] = {0, 0, -1, 1};

    int T;
    cin >> T;

    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;

        vector<string> G(N);
        for (int i = 0; i < N; ++i) cin >> G[i];

        struct Query {
            int sr, sc, er, ec, K;
        };

        vector<Query> queries(Q);

        unordered_map<long long, vector<int>> groups;
        groups.reserve(Q * 2 + 10);

        for (int i = 0; i < Q; ++i) {
            int sr, sc, er, ec, K;
            cin >> sr >> sc >> er >> ec >> K;

            // If the problem uses 1-based coordinates, uncomment these 4 lines:
            // --sr;
            // --sc;
            // --er;
            // --ec;

            queries[i] = {sr, sc, er, ec, K};

            long long key = 1LL * sr * M + sc;
            groups[key].push_back(i);
        }

        vector<string> answer(Q, "NO");

        int totalCells = N * M;
        int totalStates = totalCells * 2;

        vector<int> stamp(totalStates, 0);
        vector<int> dist(totalStates, 0);

        int curStamp = 0;

        vector<int> q;
        q.reserve(totalStates);

        for (auto &it : groups) {
            const vector<int> &ids = it.second;

            int sr = int(it.first / M);
            int sc = int(it.first % M);

            int maxK = 0;
            bool hasValidQuery = false;

            for (int id : ids) {
                if (queries[id].K >= 0) {
                    hasValidQuery = true;
                    maxK = max(maxK, queries[id].K);
                }
            }

            if (!hasValidQuery) continue;

            ++curStamp;
            q.clear();

            auto pushState = [&](int r, int c, int mode, int d) {
                int cell = r * M + c;
                int idx = cell * 2 + mode;

                if (stamp[idx] != curStamp) {
                    stamp[idx] = curStamp;
                    dist[idx] = d;
                    q.push_back(idx);
                }
            };

            // Start always in mode 0
            pushState(sr, sc, 0, 0);

            size_t head = 0;

            while (head < q.size()) {
                int state = q[head++];

                int mode = state & 1;
                int cell = state >> 1;

                int r = cell / M;
                int c = cell % M;

                int d = dist[state];

                // No need to expand further than maxK
                if (d >= maxK) continue;

                // Toggle mode on a normal cell
                if (G[r][c] == '.') {
                    int nmode = mode ^ 1;
                    int nidx = cell * 2 + nmode;

                    if (stamp[nidx] != curStamp) {
                        stamp[nidx] = curStamp;
                        dist[nidx] = d + 1;
                        q.push_back(nidx);
                    }
                }

                // Move orthogonally
                for (int k = 0; k < 4; ++k) {
                    int nr = r + DR[k];
                    int nc = c + DC[k];

                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;

                    char ch = G[nr][nc];

                    bool canMove =
                        (ch == '.') ||
                        (mode == 0 && ch == 'B') ||
                        (mode == 1 && ch == 'R');

                    if (!canMove) continue;

                    int ncell = nr * M + nc;
                    int nidx = ncell * 2 + mode;

                    if (stamp[nidx] != curStamp) {
                        stamp[nidx] = curStamp;
                        dist[nidx] = d + 1;
                        q.push_back(nidx);
                    }
                }
            }

            for (int id : ids) {
                const Query &qr = queries[id];

                if (qr.K < 0) continue;

                // Already at the destination
                if (qr.sr == qr.er && qr.sc == qr.ec) {
                    answer[id] = "YES";
                    continue;
                }

                int endCell = qr.er * M + qr.ec;
                char endChar = G[qr.er][qr.ec];

                int best = INT_MAX;

                for (int mode = 0; mode < 2; ++mode) {
                    bool canStay =
                        (endChar == '.') ||
                        (mode == 0 && endChar == 'B') ||
                        (mode == 1 && endChar == 'R');

                    if (!canStay) continue;

                    int idx = endCell * 2 + mode;

                    if (stamp[idx] == curStamp) {
                        best = min(best, dist[idx]);
                    }
                }

                if (best <= qr.K) {
                    answer[id] = "YES";
                }
            }
        }

        for (const string &s : answer) {
            cout << s << '\n';
        }
    }

    return 0;
}