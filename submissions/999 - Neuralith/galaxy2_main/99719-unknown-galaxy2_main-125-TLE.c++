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

        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].sr >> queries[i].sc
                >> queries[i].er >> queries[i].ec >> queries[i].K;
            // If the problem uses 1-based coordinates, uncomment:
            // --queries[i].sr; --queries[i].sc;
            // --queries[i].er; --queries[i].ec;
        }

        // Group queries by starting cell
        unordered_map<long long, vector<int>> groups;
        groups.reserve(Q * 2 + 10);

        for (int i = 0; i < Q; ++i) {
            long long key = 1LL * queries[i].sr * M + queries[i].sc;
            groups[key].push_back(i);
        }

        vector<string> answer(Q, "NO");

        int totalCells = N * M;
        int totalStates = totalCells * 2;

        vector<int> stamp(totalStates, 0);
        vector<int> dist(totalStates, 0);
        int curStamp = 0;

        vector<int> bfsQ;
        bfsQ.reserve(totalStates);

        auto compatible = [&](int r, int c, int mode) {
            char ch = G[r][c];
            return ch == '.' || (mode == 0 && ch == 'B') || (mode == 1 && ch == 'R');
        };

        for (auto &it : groups) {
            const vector<int> &ids = it.second;
            int sr = int(it.first / M);
            int sc = int(it.first % M);

            // Build end-state map for this start group
            unordered_map<int, vector<int>> endMap;
            endMap.reserve(ids.size() * 2 + 10);
            int maxK = 0;

            for (int id : ids) {
                const Query &qr = queries[id];
                maxK = max(maxK, qr.K);
                int endCell = qr.er * M + qr.ec;
                char endCh = G[qr.er][qr.ec];
                for (int mode = 0; mode < 2; ++mode) {
                    if (compatible(qr.er, qr.ec, mode)) {
                        int endState = (endCell << 1) | mode;
                        endMap[endState].push_back(id);
                    }
                }
            }

            ++curStamp;
            bfsQ.clear();

            auto pushState = [&](int r, int c, int mode, int d) {
                int cell = r * M + c;
                int idx = (cell << 1) | mode;
                if (stamp[idx] != curStamp) {
                    stamp[idx] = curStamp;
                    dist[idx] = d;
                    bfsQ.push_back(idx);
                }
            };

            pushState(sr, sc, 0, 0);

            int unanswered = (int)ids.size();
            vector<char> localAnswered(ids.size(), 0);
            unordered_map<int, int> idToLocal;
            idToLocal.reserve(ids.size() * 2 + 10);
            for (int i = 0; i < (int)ids.size(); ++i) {
                idToLocal[ids[i]] = i;
            }

            size_t head = 0;

            while (head < bfsQ.size() && unanswered > 0) {
                int state = bfsQ[head++];
                int mode = state & 1;
                int cell = state >> 1;
                int r = cell / M;
                int c = cell % M;
                int d = dist[state];

                // Check if this state satisfies any pending query
                auto itEnd = endMap.find(state);
                if (itEnd != endMap.end()) {
                    for (int id : itEnd->second) {
                        int lid = idToLocal[id];
                        if (!localAnswered[lid] && d <= queries[id].K) {
                            localAnswered[lid] = 1;
                            answer[id] = "YES";
                            --unanswered;
                        }
                    }
                }

                if (unanswered == 0) break;
                if (d >= maxK) continue;

                // Spin on '.'
                if (G[r][c] == '.') {
                    int nmode = mode ^ 1;
                    int nidx = (cell << 1) | nmode;
                    if (stamp[nidx] != curStamp) {
                        stamp[nidx] = curStamp;
                        dist[nidx] = d + 1;
                        bfsQ.push_back(nidx);
                    }
                }

                // Orthogonal moves
                for (int k = 0; k < 4; ++k) {
                    int nr = r + DR[k];
                    int nc = c + DC[k];
                    if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
                    if (!compatible(nr, nc, mode)) continue;

                    int ncell = nr * M + nc;
                    int nidx = (ncell << 1) | mode;
                    if (stamp[nidx] != curStamp) {
                        stamp[nidx] = curStamp;
                        dist[nidx] = d + 1;
                        bfsQ.push_back(nidx);
                    }
                }
            }
        }

        for (const string &s : answer) {
            cout << s << '\n';
        }
    }
    return 0;
}