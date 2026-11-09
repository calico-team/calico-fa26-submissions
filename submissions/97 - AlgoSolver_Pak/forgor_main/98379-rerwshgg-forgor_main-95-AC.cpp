#include <bits/stdc++.h>
using namespace std;
const int MOD = 200001;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    if (!(cin >> phase)) return 0;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<vector<int>> adj(N + 1);
        vector<int> deg(N + 1, 0);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }

        vector<int> prufer;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= N; i++) if (deg[i] == 1) pq.push(i);
        vector<int> deg2 = deg;
        for (int i = 0; i < N - 2; i++) {
            int leaf = pq.top(); pq.pop();
            int nb = -1;
            for (int v : adj[leaf]) if (deg2[v] > 0) { nb = v; break; }
            prufer.push_back(nb);
            deg2[leaf] = 0;
            deg2[nb]--;
            if (deg2[nb] == 1) pq.push(nb);
        }

        long long sum = 0;
        for (int x : prufer) sum += x;
        int S = (int)(sum % MOD);

        for (int i = 0; i < (int)prufer.size(); i++) {
            if (i) cout << ' ';
            cout << prufer[i];
        }
        if (N > 2) cout << ' ';
        cout << S << ' ' << S << '\n';
        return 0;
    }

    // SECOND
    vector<long long> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    int bad = -1;
    for (int i = 0; i < N; i++) if (A[i] == -1) bad = i;

    vector<int> prufer;
    if (N > 2) prufer.assign(N - 2, 0);

    int S = 0;
    if (A[N - 2] != -1) S = (int)A[N - 2];
    else S = (int)A[N - 1];

    if (N > 2) {
        if (bad >= 0 && bad < N - 2) {
            long long sumOthers = 0;
            for (int i = 0; i < N - 2; i++) if (i != bad) sumOthers += A[i];
            long long miss = (S - (sumOthers % MOD)) % MOD;
            if (miss < 0) miss += MOD;
            prufer[bad] = (int)miss;
            for (int i = 0; i < N - 2; i++) if (i != bad) prufer[i] = (int)A[i];
        } else {
            for (int i = 0; i < N - 2; i++) prufer[i] = (int)A[i];
        }
    }

    if (N == 2) {
        cout << "1 2\n";
        return 0;
    }

    vector<int> deg(N + 1, 1);
    for (int x : prufer) deg[x]++;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= N; i++) if (deg[i] == 1) pq.push(i);
    for (int x : prufer) {
        int leaf = pq.top(); pq.pop();
        cout << leaf << ' ' << x << '\n';
        deg[leaf]--;
        deg[x]--;
        if (deg[x] == 1) pq.push(x);
    }
    int u = pq.top(); pq.pop();
    int v = pq.top(); pq.pop();
    cout << u << ' ' << v << '\n';
    return 0;
}