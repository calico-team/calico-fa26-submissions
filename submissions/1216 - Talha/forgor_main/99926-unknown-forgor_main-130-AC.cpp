#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N + 1);
    for (auto& e : E) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    vector<int> parent(N + 1, 0);
    vector<int> q = {1};
    parent[1] = -1;
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        for (int v : adj[u]) {
            if (parent[v] == 0) {
                parent[v] = u;
                q.push_back(v);
            }
        }
    }
    vector<int> A(N);
    int xor_sum = 0;
    for (int i = 2; i <= N; i++) {
        A[i - 1] = parent[i];
        xor_sum ^= parent[i];
    }
    A[0] = xor_sum;
    return A;
}

vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int missing_idx = -1;
    for (int i = 0; i < N; i++) {
        if (A[i] == -1) missing_idx = i;
    }
    if (missing_idx != 0) {
        int xor_others = A[0];
        for (int i = 1; i < N; i++) {
            if (i != missing_idx) xor_others ^= A[i];
        }
        A[missing_idx] = xor_others;
    }
    vector<pair<int, int>> edges;
    for (int i = 2; i <= N; i++) {
        edges.push_back({i, A[i - 1]});
    }
    return edges;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string phase;
    if (!(cin >> phase)) return 0;
    int N; cin >> N;
    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) cin >> E[i].first >> E[i].second;
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) cin >> A[i];
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) cout << e.first << ' ' << e.second << '\n';
    }
}