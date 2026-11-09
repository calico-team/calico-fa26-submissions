#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;

/**
 * Output a list N integers A_1 .. A_N
 *
 * N: the number of vertices
 * E: the N - 1 edges of the tree as (u, v) pairs
 */
vector<int> solve_phase1(int N, vector<pair<int, int>>& E) {
    vector<int> v;
    int sum=0;
    for(int i=0; i<N; i++){
        v.push_back(E.first());
        v.push_back(E.second());
        sum+=E.first()+E.second();
        sum=sum%1000000;
    }
    v.push_back(sum);
    return v;
}

/**
 * The N - 1 edges of the original tree as (u, v) pairs
 *
 * N: the number of vertices
 * A: the N integers A_1 .. A_N with one value replaced with -1
 */
vector<pair<int, int>> solve_phase2(int N, vector<int>& A) {
    int sum=0, index;
    vector<pair<int, int>> ans;
    if(A[A.size()-1]==-1){
        index=0;
    }
    else{
        for(int i=0; i<A.size()-1; i++){
            sum+=A[i];
            sum=sum%1000000;
            if(A[i]==-1) index=i;
        }
        A[index]=A[A.size()-1]-sum;
    }
    for(int i=0; i<A.size()-1; i+=2){
        ans.push_back(make_pair(A[i], A[i]+1));
    }
    return ans;
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