#include <bits/stdc++.h>
using namespace std;
/**
 * Output a List N integers A_1 .. A_N
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N + 1);
    for (auto& edge : E) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
    vector<int> parent(N + 1, 0);
    vector<bool> visited(N + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    int xor_sum = 0;
    for (int i = 2; i <= N; ++i) {
        xor_sum ^= parent[i];
    }
    vector<int> A(N);
    A[0] = xor_sum;
    for (int i = 2; i <= N; ++i) {
        A[i - 1] = parent[i];
    }
    return A;
}
/**
 * The N - 1 edges of the original tree as (u, v) pairs
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int missing_idx = -1;
    for (int i = 0; i < N; ++i) {
        if (A[i] == -1) {
            missing_idx = i;
            break;
        }
    }
    vector<pair<int, int>> edges;
    if (missing_idx == 0) {
        for (int i = 2; i <= N; ++i) {
            edges.push_back({i, A[i - 1]});
        }
    } 
    else {
        int current_xor = 0;
        for (int i = 1; i < N; ++i) {
            if (i != missing_idx) {
                current_xor ^= A[i];
            }
        }
        int missing_node = missing_idx + 1;
        int recovered_parent = A[0] ^ current_xor;
        edges.push_back({missing_node, recovered_parent});
        for (int i = 2; i <= N; ++i) {
            if (i != missing_node) {
                edges.push_back({i, A[i - 1]});
            }
        }
    }
    return edges;
}
int main() {
    string phase;
    cin >> phase;
    int N;
    cin >> N;
    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; ++i) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; ++i) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}