#include <bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M, K; cin >> N >> M >> K;
        vector<vector<int>> adj(N);
        queue<int> q{};
        vector<int> dist(N);
        vector<int> sem(M+1);
        int curr = 1;
        for (int i=0; i < N; i++) {
            int p; cin >> p;
            if (p>0) adj[p-1].push_back(i);
            else {
                if (curr>M) continue;
                q.push(i);
                sem[curr]++;
                dist[i] = curr;
                if (sem[curr]==K) curr++;
            }
        }

        int ans = 0;
        while (!q.empty()) {
            int n = q.front();
            ans++;
            curr = max(curr, dist[n]+1);
            q.pop();
            for (auto& i : adj[n]) {
                if (curr > M) continue;
                dist[i] = curr;
                sem[curr]++;
                if (sem[curr]==K) curr++;
                q.push(i);
            }
        }

        cout << ans << '\n';
    }
}