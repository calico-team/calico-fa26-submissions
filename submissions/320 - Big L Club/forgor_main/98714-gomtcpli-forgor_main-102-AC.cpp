#include <bits/stdc++.h>
using namespace std;
#define int long long

// https://cp-algorithms.com/graph/pruefer_code.html

vector<vector<int>> adj;

vector<int> pruefer_code() {
    int n = adj.size();
    set<int> leafs;
    vector<int> degree(n);
    vector<bool> killed(n, false);
    for (int i = 0; i < n; i++) {
        degree[i] = adj[i].size();
        if (degree[i] == 1)
            leafs.insert(i);
    }

    vector<int> code(n - 2);
    for (int i = 0; i < n - 2; i++) {
        int leaf = *leafs.begin();
        leafs.erase(leafs.begin());
        killed[leaf] = true;

        int v;
        for (int u : adj[leaf]) {
            if (!killed[u])
                v = u;
        }

        code[i] = v;
        if (--degree[v] == 1)
            leafs.insert(v);
    }

    return code;
}

vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
    int n = code.size() + 2;
    vector<int> degree(n, 1);
    for (int i : code)
        degree[i]++;

    int ptr = 0;
    while (degree[ptr] != 1)
        ptr++;
    int leaf = ptr;

    vector<pair<int, int>> edges;
    for (int v : code) {
        edges.emplace_back(leaf, v);
        if (--degree[v] == 1 && v < ptr) {
            leaf = v;
        } else {
            ptr++;
            while (degree[ptr] != 1)
                ptr++;
            leaf = ptr;
        }
    }
    edges.emplace_back(leaf, n-1);
    return edges;
}

int N;

vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    adj.clear(); adj.resize(N);

    for(pair<int,int> &p : E){
        adj[p.first-1].push_back(p.second-1);
        adj[p.second-1].push_back(p.first-1);
    }

    vector<int> A = pruefer_code();

    int sum = accumulate(A.begin(),A.end(),(int)0);

    A.push_back(sum % N);
    A.push_back(sum % N);

    return A;
}

vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {\

    int idx;

    for(int i = 0; i < A.size(); ++i){
        if(A[i] == -1){
            idx = i;
            break;
        }
    }

    if(idx < N-2){
        int sum = 0;

        for(int i = 0; i < N-2; ++i){
            if(i != idx) 
                sum += A[i];
        }
        
        A[idx] = ((A[N-2] - sum) % N + 4*N) % N;
    }

    vector<int> code(A.begin(), A.begin() + N-2);

    vector<pair<int, int>> edges = pruefer_decode(code);

    for(pair<int,int> &e : edges){
        e.first++; 
        e.second++;
    }

    return edges;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    string phase;
    cin >> phase;

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