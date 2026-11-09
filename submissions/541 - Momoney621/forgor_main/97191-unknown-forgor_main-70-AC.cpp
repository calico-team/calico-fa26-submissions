#include <iostream>
#include <vector>
#include <string>
using namespace std;


vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adjacent(N + 1);
    vector<int> degree(N + 1);
    for (auto& [u, v] : E) {
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    vector<int> parent(N + 1), order = {N};
    for (int i = 0; i < (int)order.size(); i++){
        for (int next : adjacent[order[i]]){
            if (next != parent[order[i]]) {
                parent[next] = order[i];
                order.push_back(next);
            }
        }
    }
    vector<int> A(N, 0);
    int pointer = 1;
    while (degree[pointer] != 1) pointer++;
    int leaf = pointer;
    for (int i = 0; i < N - 2; i++) {
        int up = parent[leaf];
        A[i] = up;
        A[N - 2] ^= up;
        if (--degree[up] == 1 && up < pointer) {
            leaf = up;
        } else {
            pointer++;
            while (degree[pointer] != 1) pointer++;
            leaf = pointer;
        }
    }
    return A;
}


vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    for (int i = 0; i < N - 2; i++) {
        if (A[i] != -1) continue;
        A[i] = A[N - 2];
        for (int j = 0; j < N - 2; j++)
            if (j != i){
                A[i] ^= A[j];
            }
    }

    vector<int> degree(N + 1, 1);
    for (int i = 0; i < N - 2; i++){
        degree[A[i]]++;
    }
    vector<pair<int, int>> edges;
    int pointer = 1;
    while (degree[pointer] != 1) pointer++;
    int leaf = pointer;
    for (int i = 0; i < N - 2; i++) {
        edges.push_back({leaf, A[i]});
        if (--degree[A[i]] == 1 && A[i] < pointer) {
            leaf = A[i];
        } else {
            pointer++;
            while (degree[pointer] != 1) pointer++;
            leaf = pointer;
        }
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
