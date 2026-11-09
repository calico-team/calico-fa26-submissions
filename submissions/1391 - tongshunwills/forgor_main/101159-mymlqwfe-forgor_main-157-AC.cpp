#include <bits/stdc++.h>
using namespace std;

vector<int> amnesiac(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> x(N + 1);
    for (auto& e : E) {
        x[e.first].push_back(e.second);
        x[e.second].push_back(e.first);
    }
    vector<int> x1(N + 1, -1), x2 = {1};
    x1[1] = 0;
    for (int i = 0; i < (int)x2.size(); i++) {
        for (int v : x[x2[i]]) {
            if (x1[v] != -1) continue;
            x1[v] = x2[i];
            x2.push_back(v);
        }
    }
    return x1;
}

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solvePhase1(int N, vector<pair<int, int>>& E) {
    vector<int> x = amnesiac(N, E);
    vector<int> A(N, 0);
    long long x1 = 0;
    for (int i = 2; i <= N; i++) {
        A[i - 1] = x[i];
        x1 += x[i];
    }
    A[0] = x1 % (N + 1);
    return A;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solvePhase2(int N, vector<int>& A) {
    int x = -1;
    long long x1 = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] == -1) x = i;
        else if (i > 0) x1 += A[i];
    }
    if (x > 0) A[x] = ((A[0] - x1) % (N + 1) + (N + 1)) % (N + 1);
    vector<pair<int, int>> x2;///WHAT DOES X1 EVEN MEAN AT THIS POINT IF THIS AC IM OGING TO PRAY TO MECCA
    for (int i = 2; i <= N; i++) x2.push_back({i, A[i - 1]});
    return x2;
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
        vector<int> A = solvePhase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << endl;
    } else {
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
        vector<pair<int, int>> edges = solvePhase2(N, A);
        for (auto& e : edges) {
            cout << e.first << ' ' << e.second << endl;
        }
    }
}