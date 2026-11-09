#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
// Scheme: store the Pruefer sequence P (N-2 values, each <= N < 2^18) in A_1..A_{N-2},
// A_{N-1} = 0 (unused), A_N = XOR of all P. Any single erased P_i is recovered from the XOR.

vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N + 1);
    vector<int> deg(N + 1, 0);
    for (auto& e : E) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
        deg[e.first]++; deg[e.second]++;
    }
    // root at N
    vector<int> parent(N + 1, 0), order = {N};
    parent[N] = -1;
    for (size_t i = 0; i < order.size(); i++)
        for (int v : adj[order[i]])
            if (v != parent[order[i]]) { parent[v] = order[i]; order.push_back(v); }
    vector<int> P;
    int ptr = 1;
    while (deg[ptr] != 1) ptr++;
    int leaf = ptr;
    for (int i = 0; i < N - 2; i++) {
        int nxt = parent[leaf];
        P.push_back(nxt);
        if (--deg[nxt] == 1 && nxt < ptr) leaf = nxt;
        else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
    }
    vector<int> A(N, 0);
    int x = 0;
    for (int i = 0; i < N - 2; i++) { A[i] = P[i]; x ^= P[i]; }
    A[N - 1] = x;
    return A;
}

vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    vector<int> P(A.begin(), A.begin() + (N - 2));
    int miss = -1, x = 0;
    for (int i = 0; i < N - 2; i++) { if (P[i] == -1) miss = i; else x ^= P[i]; }
    if (miss != -1) P[miss] = A[N - 1] ^ x; // A[N-1] is intact when a P value is erased
    vector<int> deg(N + 1, 1);
    for (int p : P) deg[p]++;
    vector<pair<int, int>> edges;
    int ptr = 1;
    while (deg[ptr] != 1) ptr++;
    int leaf = ptr;
    for (int i = 0; i < N - 2; i++) {
        int p = P[i];
        edges.push_back({leaf, p});
        if (--deg[p] == 1 && p < ptr) leaf = p;
        else { ptr++; while (deg[ptr] != 1) ptr++; leaf = ptr; }
    }
    edges.push_back({leaf, N});
    return edges;
}

int main() {
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
