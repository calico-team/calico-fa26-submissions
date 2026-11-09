#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;

int N, M, S;
vector<string> G;
vector<char> act;
vector<int> pre, suf;

void sweep(bool rev, vector<int>& out) {
    out.assign((size_t)M * S * S, INF);
    int W = 2 * S;
    vector<int> d(W * W);
    for (int i = 0; i < M; i++) {
        int c = rev ? M - 1 - i : i;
        int p = rev ? c + 1 : c - 1;
        fill(d.begin(), d.end(), INF);
        for (int k = 0; k < W; k++) d[k * W + k] = 0;
        if (i > 0)
            for (int u = 0; u < S; u++)
                for (int v = 0; v < S; v++)
                    d[u * W + v] = out[(size_t)p * S * S + u * S + v];
        for (int u = 0; u < S; u++) {
            if (!act[c * S + u]) continue;
            int r = u >> 1;
            if (r + 1 < N && act[c * S + u + 2])
                d[(S + u) * W + S + u + 2] = d[(S + u + 2) * W + S + u] = 1;
            if (i > 0 && act[p * S + u])
                d[u * W + S + u] = d[(S + u) * W + u] = 1;
            if (!(u & 1) && G[r][c] == '.')
                d[(S + u) * W + S + u + 1] = d[(S + u + 1) * W + S + u] = 1;
        }
        for (int k = 0; k < W; k++)
            for (int a = 0; a < W; a++) {
                int x = d[a * W + k];
                if (x >= INF) continue;
                for (int b = 0; b < W; b++) {
                    int y = d[k * W + b];
                    if (y < INF && x + y < d[a * W + b]) d[a * W + b] = x + y;
                }
            }
        for (int u = 0; u < S; u++)
            for (int v = 0; v < S; v++)
                out[(size_t)c * S * S + u * S + v] = d[(S + u) * W + S + v];
    }
}

void search(int l, int r, int src, vector<int>& dist) {
    int len = r - l + 1;
    dist.assign((size_t)len * S, INF);
    vector<pair<int, int>> q;
    size_t head = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    q.push_back({0, src});
    auto push = [&](int y, int nd) {
        if (nd < dist[y]) { dist[y] = nd; q.push_back({nd, y}); }
    };
    while (head < q.size() || !pq.empty()) {
        int d, x;
        if (!pq.empty() && (head == q.size() || pq.top().first <= q[head].first)) {
            d = pq.top().first; x = pq.top().second; pq.pop();
        } else {
            d = q[head].first; x = q[head].second; head++;
        }
        if (d != dist[x]) continue;
        int c = x / S, u = x - c * S, gc = l + c, row = u >> 1;
        if (row > 0 && act[gc * S + u - 2]) push(x - 2, d + 1);
        if (row + 1 < N && act[gc * S + u + 2]) push(x + 2, d + 1);
        if (c > 0 && act[(gc - 1) * S + u]) push(x - S, d + 1);
        if (c + 1 < len && act[(gc + 1) * S + u]) push(x + S, d + 1);
        if (G[row][gc] == '.') push(x ^ 1, d + 1);
        if (c == 0) {
            const int* P = &pre[(size_t)l * S * S + u * S];
            for (int w = 0; w < S; w++)
                if (w != u && P[w] < INF && d + P[w] < dist[w]) {
                    dist[w] = d + P[w];
                    pq.push({dist[w], w});
                }
        }
        if (c == len - 1) {
            const int* P = &suf[(size_t)r * S * S + u * S];
            int base = (len - 1) * S;
            for (int w = 0; w < S; w++)
                if (w != u && P[w] < INF && d + P[w] < dist[base + w]) {
                    dist[base + w] = d + P[w];
                    pq.push({dist[base + w], base + w});
                }
        }
    }
}

vector<string> solve(int n, int m, int Q, vector<string>& g, vector<pair<int, int>>& start, vector<pair<int, int>>& end, vector<int>& K) {
    N = n; M = m; S = 2 * n; G = g;
    act.assign((size_t)M * S, 0);
    for (int c = 0; c < M; c++)
        for (int r = 0; r < N; r++) {
            char ch = G[r][c];
            act[c * S + 2 * r]     = (ch == '.' || ch == 'B');
            act[c * S + 2 * r + 1] = (ch == '.' || ch == 'R');
        }
    sweep(false, pre);
    sweep(true, suf);

    vector<string> ans(Q, "NO");
    vector<vector<int>> D(S);

    function<void(int, int, vector<int>&)> go = [&](int l, int r, vector<int>& qs) {
        if (l > r || qs.empty()) return;
        int mid = (l + r) / 2;
        vector<int> lf, rt, here;
        for (int id : qs) {
            int lo = min(start[id].second, end[id].second);
            int hi = max(start[id].second, end[id].second);
            if (hi < mid) lf.push_back(id);
            else if (lo > mid) rt.push_back(id);
            else here.push_back(id);
        }
        if (!here.empty()) {
            vector<int> srcs;
            for (int u = 0; u < S; u++)
                if (act[mid * S + u]) {
                    search(l, r, (mid - l) * S + u, D[u]);
                    srcs.push_back(u);
                }
            for (int id : here) {
                int s = (start[id].second - l) * S + start[id].first * 2;
                int t = (end[id].second - l) * S + end[id].first * 2;
                long long best = 4LL * INF;
                for (int u : srcs) {
                    int a = D[u][s];
                    int b = min(D[u][t], D[u][t + 1]);
                    if (a < INF && b < INF) best = min(best, (long long)a + b);
                }
                if (best <= K[id]) ans[id] = "YES";
            }
        }
        go(l, mid - 1, lf);
        go(mid + 1, r, rt);
    };
    vector<int> all(Q);
    iota(all.begin(), all.end(), 0);
    go(0, M - 1, all);
    return ans;
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
