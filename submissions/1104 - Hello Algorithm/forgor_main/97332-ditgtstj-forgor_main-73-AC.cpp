#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000001;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string phase;
    cin >> phase;

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

        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 1; i <= N; i++) {
            if (deg[i] == 1)
                pq.push(i);
        }

        vector<int> code;
        long long checksum = 0;

        for (int i = 0; i < N - 2; i++) {
            int leaf = pq.top();
            pq.pop();

            int neighbor = 0;

            for (int v : adj[leaf]) {
                if (deg[v] > 0) {
                    neighbor = v;
                    break;
                }
            }

            code.push_back(neighbor);
            checksum = (checksum + neighbor) % MOD;

            deg[leaf] = 0;
            deg[neighbor]--;

            if (deg[neighbor] == 1)
                pq.push(neighbor);
        }

        for (int x : code)
            cout << x << ' ';

        cout << checksum << " 0\n";
    }
    else {
        vector<int> A(N);

        for (int i = 0; i < N; i++)
            cin >> A[i];

        int missing = -1;

        for (int i = 0; i < N; i++) {
            if (A[i] == -1)
                missing = i;
        }

        if (missing < N - 2) {
            long long sum = 0;

            for (int i = 0; i < N - 2; i++) {
                if (i != missing)
                    sum += A[i];
            }

            A[missing] = (A[N-2] - sum % MOD + MOD) % MOD;
        }

        vector<int> deg(N + 1, 1);

        for (int i = 0; i < N - 2; i++)
            deg[A[i]]++;

        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 1; i <= N; i++) {
            if (deg[i] == 1)
                pq.push(i);
        }

        for (int i = 0; i < N - 2; i++) {
            int leaf = pq.top();
            pq.pop();

            int v = A[i];

            cout << leaf << ' ' << v << '\n';

            deg[leaf]--;
            deg[v]--;

            if (deg[v] == 1)
                pq.push(v);
        }

        int u = pq.top();
        pq.pop();
        int v = pq.top();

        cout << u << ' ' << v << '\n';
    }

    return 0;
}
