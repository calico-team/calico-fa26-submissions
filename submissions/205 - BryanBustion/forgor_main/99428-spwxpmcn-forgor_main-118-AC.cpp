#include <bits/stdc++.h>
using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N + 1);
    vector<int> deg(N + 1, 0);
    for (auto &e : E) {
        int u = e.first;
        int v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 1) {
            pq.push(i);
        }
    }
    vector<int> p;
    int xr = 0;
    for (int i = 0; i < N - 2; i++) {
        int u = pq.top();
        pq.pop();
        for (int v : adj[u]) {
            if (deg[v] > 0) {
                p.push_back(v);
                xr ^= v;
                deg[u]--;
                deg[v]--;
                if (deg[v] == 1) {
                    pq.push(v);
                }
                break;
            }
        }
    }
    vector<int> A(N, 0);
    for (int i = 0; i < N - 2; i++) {
        A[i] = p[i];
    }
    A[N - 2] = xr;
    A[N - 1] = 0;
    return A;
}

vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    vector<int> p(N - 2);
    int missing = -1;
    for (int i = 0; i < N - 2; i++) {
        if (A[i] == -1) {
            missing = i;
            break;
        }
    }
    for (int i = 0; i < N - 2; i++) {
        p[i] = A[i];
    }
    if (missing != -1) {
        int xr = A[N - 2];
        for (int i = 0; i < N - 2; i++) {
            if (i != missing) {
                xr ^= A[i];
            }
        }
        p[missing] = xr;
    }
    vector<int> deg(N + 1, 1);
    for (int v : p) {
        deg[v]++;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= N; i++) {
        if (deg[i] == 1) {
            pq.push(i);
        }
    }
    vector<pair<int, int>> edges;
    for (int v : p) {
        int u = pq.top();
        pq.pop();
        edges.push_back({u, v});
        deg[u]--;
        deg[v]--;
        if (deg[v] == 1) {
            pq.push(v);
        }
    }
    int u = pq.top();
    pq.pop();
    int v = pq.top();
    pq.pop();
    edges.push_back({u, v});
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