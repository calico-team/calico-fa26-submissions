#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
vector<string> G;
vector<int> sr, sc, er, ec, K;
vector<int> best;
const int INF = 2000000000;

bool is_open(int r, int c, int mode) {
    char ch = G[r][c];
    if (ch == '.') return true;
    if (ch == 'B') return mode == 0;
    return mode == 1;
}

void work(int l, int r, vector<int>& qs) {
    if (qs.empty() || l > r) return;
    int mid = (l + r) / 2;
    int len = r - l + 1;
    int states = N * len * 2;

    vector<int> dist;
    int cnt = 0;
    vector<int> q(states);
    static const int dx[4] = {1, -1, 0, 0};
    static const int dy[4] = {0, 0, 1, -1};

    for (int row = 0; row < N; row++) {
        for (int mode = 0; mode < 2; mode++) {
            if (!is_open(row, mid, mode)) continue;
            dist.resize((size_t)(cnt + 1) * states, INF);
            int* d = &dist[(size_t)cnt * states];
            int head = 0, tail = 0;
            int first = ((row * len) + (mid - l)) * 2 + mode;
            d[first] = 0;
            q[tail++] = first;
            while (head < tail) {
                int cur = q[head++];
                int m = cur % 2;
                int cell = cur / 2;
                int x = cell / len;
                int y = cell % len + l;
                int nd = d[cur] + 1;
                if (G[x][y] == '.') {
                    int other = cur ^ 1;
                    if (d[other] == INF) { d[other] = nd; q[tail++] = other; }
                }
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k], ny = y + dy[k];
                    if (nx < 0 || nx >= N || ny < l || ny > r) continue;
                    if (!is_open(nx, ny, m)) continue;
                    int nxt = ((nx * len) + (ny - l)) * 2 + m;
                    if (d[nxt] == INF) { d[nxt] = nd; q[tail++] = nxt; }
                }
            }
            cnt++;
        }
    }

    vector<int> leftQ, rightQ;
    for (int id : qs) {
        int a = ((sr[id] * len) + (sc[id] - l)) * 2 + 0;
        for (int mode = 0; mode < 2; mode++) {
            if (!is_open(er[id], ec[id], mode)) continue;
            int b = ((er[id] * len) + (ec[id] - l)) * 2 + mode;
            for (int j = 0; j < cnt; j++) {
                int da = dist[(size_t)j * states + a];
                int db = dist[(size_t)j * states + b];
                if (da == INF || db == INF) continue;
                best[id] = min(best[id], da + db);
            }
        }
        if (sc[id] < mid && ec[id] < mid) leftQ.push_back(id);
        else if (sc[id] > mid && ec[id] > mid) rightQ.push_back(id);
    }
    work(l, mid - 1, leftQ);
    work(mid + 1, r, rightQ);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    string out;
    while (T--) {
        cin >> N >> M >> Q;
        G.assign(N, "");
        for (int i = 0; i < N; i++) cin >> G[i];
        sr.assign(Q, 0); sc.assign(Q, 0); er.assign(Q, 0); ec.assign(Q, 0); K.assign(Q, 0);
        for (int i = 0; i < Q; i++) cin >> sr[i] >> sc[i] >> er[i] >> ec[i] >> K[i];
        best.assign(Q, INF);
        vector<int> all(Q);
        for (int i = 0; i < Q; i++) all[i] = i;
        work(0, M - 1, all);
        for (int i = 0; i < Q; i++) out += (best[i] <= K[i]) ? "YES\n" : "NO\n";
    }
    cout << out;
    return 0;
}