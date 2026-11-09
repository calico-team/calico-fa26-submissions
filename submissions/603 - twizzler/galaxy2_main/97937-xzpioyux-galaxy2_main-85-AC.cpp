#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
vector<string> G;
vector<int> sr, sc, er, ec, KK, best;
const int INF = 2000000000;

inline bool act(int r, int c, int m) {
    char x = G[r][c];
    return x == '.' || (x == 'B' && m == 0) || (x == 'R' && m == 1);
}

void solve(int l, int r, vector<int> &ids) {
    if (ids.empty() || l > r) return;
    int mid = (l + r) / 2;
    int W = r - l + 1, S = W * N * 2;
    vector<int> srcs;
    for (int row = 0; row < N; row++)
        for (int m = 0; m < 2; m++)
            if (act(row, mid, m)) srcs.push_back(((mid - l) * N + row) * 2 + m);

    vector<vector<int>> dist(srcs.size(), vector<int>(S, INF));
    vector<int> qu(S);
    static const int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    for (size_t k = 0; k < srcs.size(); k++) {
        vector<int> &d = dist[k];
        int h = 0, t = 0;
        qu[t++] = srcs[k];
        d[srcs[k]] = 0;
        while (h < t) {
            int st = qu[h++];
            int m = st & 1, tt = st >> 1;
            int row = tt % N, c = l + tt / N;
            int cd = d[st];
            for (int j = 0; j < 4; j++) {
                int nr = row + dr[j], nc = c + dc[j];
                if (nr < 0 || nr >= N || nc < l || nc > r) continue;
                if (!act(nr, nc, m)) continue;
                int ns = ((nc - l) * N + nr) * 2 + m;
                if (d[ns] == INF) { d[ns] = cd + 1; qu[t++] = ns; }
            }
            if (G[row][c] == '.') {
                int ns = st ^ 1;
                if (d[ns] == INF) { d[ns] = cd + 1; qu[t++] = ns; }
            }
        }
    }

    vector<int> left, right;
    for (int id : ids) {
        int ss = ((sc[id] - l) * N + sr[id]) * 2 + 0;
        int b = INF;
        for (size_t k = 0; k < srcs.size(); k++) {
            int ds = dist[k][ss];
            if (ds >= INF) continue;
            for (int mt = 0; mt < 2; mt++) {
                if (!act(er[id], ec[id], mt)) continue;
                int ts = ((ec[id] - l) * N + er[id]) * 2 + mt;
                int dt = dist[k][ts];
                if (dt >= INF) continue;
                b = min(b, ds + dt);
            }
        }
        best[id] = min(best[id], b);
        if (max(sc[id], ec[id]) < mid) left.push_back(id);
        else if (min(sc[id], ec[id]) > mid) right.push_back(id);
    }
    dist.clear();
    dist.shrink_to_fit();
    solve(l, mid - 1, left);
    solve(mid + 1, r, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M >> Q;
        G.assign(N, "");
        for (int i = 0; i < N; i++) cin >> G[i];
        sr.assign(Q, 0); sc = sr; er = sr; ec = sr; KK = sr;
        best.assign(Q, INF);
        for (int i = 0; i < Q; i++)
            cin >> sr[i] >> sc[i] >> er[i] >> ec[i] >> KK[i];
        vector<int> ids(Q);
        iota(ids.begin(), ids.end(), 0);
        solve(0, M - 1, ids);
        for (int i = 0; i < Q; i++)
            cout << (best[i] <= KK[i] ? "YES" : "NO") << "\n";
    }
    return 0;
}
