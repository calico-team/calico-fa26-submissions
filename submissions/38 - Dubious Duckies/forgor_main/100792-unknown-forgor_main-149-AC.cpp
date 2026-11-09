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
    for (const auto& edge : E) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }

    // BFS
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

    vector<int> A(N, 0);
    int checksum = 0;
    
    for (int i = 2; i <= N; ++i) {
        A[i - 1] = parent[i];
        checksum ^= parent[i];
    }
    
    A[0] = checksum;

    return A;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int xorsum = 0;
    for (int i = 0; i < N; ++i) {
        if (A[i] != -1) {
            xorsum ^= A[i];
        }
    }

    for (int i = 0; i < N; ++i) {
        if (A[i] == -1) {
            A[i] = xorsum;
            break;
        }
    }

    vector<pair<int, int>> edges;
    for (int i = 2; i <= N; ++i) {
        edges.push_back({i, A[i - 1]});
    }

    return edges;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("00_main.in", "r", stdin);

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
