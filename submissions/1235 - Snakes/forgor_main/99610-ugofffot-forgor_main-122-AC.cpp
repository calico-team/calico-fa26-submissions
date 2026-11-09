#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N + 1);
    for (auto [u, v] : E) adj[u].push_back(v), adj[v].push_back(u);
    vector<int> p(N + 1);
    queue<int> q; q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (v != 1 && !p[v]) p[v] = u, q.push(v);
    }
    vector<int> A(N);
    for (int v = 2; v <= N; v++) A[v - 1] = p[v], A[0] ^= p[v];
    return A;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int x = 0, j = 0;
    for (int i = 0; i < N; i++) if (A[i] == -1) j = i; else x ^= A[i];
    A[j] = x;
    vector<pair<int, int>> E;
    for (int i = 1; i < N; i++) E.push_back({i + 1, A[i]});
    return E;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string phase;
    cin >> phase;
    int N;
    cin >> N;

    if (phase == "FIRST") {
        vector<pair<int, int>> E(N - 1);
        for (int i = 0; i < N - 1; i++) {
            cin >> E[i].first >> E[i].second;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solve_phase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }
}
