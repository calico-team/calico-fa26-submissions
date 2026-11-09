#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N + 1), H(N + 1, 1), Ord;
        vector<vector<int>> Ch(N + 1);
        for (int i = 1; i <= N; i++) cin >> P[i], Ch[P[i]].push_back(i);
        Ord.push_back(0);
        for (int i = 0; i < (int)Ord.size(); i++)
            for (int v : Ch[Ord[i]]) Ord.push_back(v);
        for (int i = N; i > 0; i--) H[P[Ord[i]]] = max(H[P[Ord[i]]], H[Ord[i]] + 1);
        priority_queue<pair<int, int>> Q;
        for (int v : Ch[0]) Q.push({H[v], v});
        int Ans = 0;
        for (int t = 0; t < M && !Q.empty(); t++) {
            vector<int> Took;
            for (int k = 0; k < K && !Q.empty(); k++) Took.push_back(Q.top().second), Q.pop();
            Ans += Took.size();
            for (int u : Took) for (int v : Ch[u]) Q.push({H[v], v});
        }
        cout << Ans << '\n';
    }
}