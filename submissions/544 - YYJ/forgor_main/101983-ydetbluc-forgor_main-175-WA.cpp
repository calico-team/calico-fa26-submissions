#include <bits/stdc++.h>

using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<vector<int>> adj(N,vector<int>());
    for(auto a : E){
        adj[a.first].push_back(a.second);
        adj[a.second].push_back(a.first);
    }
    vector<int> parent(N);
    parent[0] = N+1;
    vector<bool> visited(N);
    queue<int> q;
    visited[0] = true;
    q.push(0);
    while(!q.empty()){
        int node = q.front(); q.pop();
        for(int i : adj[node]){
            if(visited[i]) continue;
            parent[i] = node;
            visited[i] = true;
            q.push(i);
        }
    }
    int save_by_xor = 0;
    for(int i = 1; i < parent.size(); i++){
        save_by_xor ^= parent[i];
    }
    parent[0] = save_by_xor & 0b1111111111111111111;
    return parent;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
void solve_phase2(int N, vector<int>& A, int negindex) {
    int saved_xor = A[0];
    if(saved_xor == -1){
        //do the tree
    }else{
        //one of the values in A is -1.
        for(int i : A){
            if(i == -1) continue;
            saved_xor ^= i;
        }
        A[negindex] = saved_xor & 0b1111111111111111111;
    }
    for(int i = 1; i < A.size(); i++){
        cout<<i+1<<" ";
        cout<<A[i]+1<<'\n';
    }
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
            E[i].first--;
            E[i].second--;
        }
        vector<int> A = solve_phase1(N, E);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << ' ';
            cout << A[i];
        }
        cout << '\n';
    } else {
        int negindex = -1;
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            if(A[i] == -1) negindex = i;
        }
        solve_phase2(N, A,negindex);
    }
}



//11110100001001000000
//  110000110101000000