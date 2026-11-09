#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    // YOUR CODE HERE
    vector<vector<int>> adj(N, vector<int>(0));
    for(auto [x,y]:E){
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
    }
    vector<int> res(N,-1);
    res[0]=0;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int i=q.front();
        q.pop();
        for(auto c:adj[i]){
            if(res[c]==-1){
                res[c]=i;
                q.push(c);
            }
        }
    }
    int su=0;
    for(int i=0; i<N-1; i++){
        su=su^res[i];
    }
    res[0]=su;




    return res;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    vector<pair<int, int>> edges;
    int odd=0;
    int su=0;
    for(int i=1; i<=N-1; i++){
        if(A[i]==-1){
            odd=i;
        }
        else{
            su=su^A[i];
            edges.push_back({i+1, A[i]+1});
        }
    }
    if(odd!=0){
        su=su^A[0];
        edges.push_back({odd+1, su+1});
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
