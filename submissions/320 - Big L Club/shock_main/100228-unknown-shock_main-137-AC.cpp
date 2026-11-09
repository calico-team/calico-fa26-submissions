#include <bits/stdc++.h>
using namespace std;
#define int long long

// https://cp-algorithms.com/data_structures/disjoint_set_union.html

vector<int> parent;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

int S(int a, int b){
    return (a-b)*(a-b);
}

void solve(){
    int n, m, q; cin >> n >> m >> q;

    vector<int> R(q), C(q), P(q);

    for(int i = 0; i < q; ++i){
        cin >> R[i] >> C[i] >> P[i];
    }

    parent.resize(n*m+1);

    iota(parent.begin(), parent.end(), 0);

    vector<int> ans(n*m+2);

    // process queries backwards

    //(r-R)^2 + (c-C)^2 <= P^2 -> 

    // (r-R)^2 <= P^2 - (c-C)^2 -> U
    // (c-C)^2 <= P^2 - (r-R)^2 -> D

    for(int i = q-1; i >= 0; --i){

        for(int r = R[i]+P[i]; r >= R[i]-P[i]; --r){

            int U = r*m + C[i] - floor(sqrt(P[i]*P[i] - S(r,R[i])));
            int D = r*m + C[i] + floor(sqrt(P[i]*P[i] - S(r,R[i])));

            for(int v = find_set(U); v <= D; v = find_set(v)){
                int c = v - r*m; // +- 1

                ans[v] = P[i]*P[i] - S(r,R[i]) - S(c,C[i])+ 1;

                parent[v] = v+1;
            }
        }
    }

    for(int i = 0; i < n*m; ++i){
        cout << ans[i] << " ";
        if(((i+1)%m) == 0) cout << "\n";
    }

}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1; cin >> t;

    while(t--){
        parent.clear();
        solve();
    }

}