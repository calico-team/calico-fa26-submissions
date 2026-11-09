#include <bits/stdc++.h>
using namespace std;

struct hashFunction{
  size_t operator()(const pair<int , int> &x) const{
    return x.first ^ x.second;
  }
};
long long solve(int n, int k, vector<tuple<int, int, int, char>> l){
    long long res=0;
    for(int i=0; i<k; i++){
        unordered_set<pair<int, int>, hashFunction> visit;
        for(int j=0; j<n; j++){
            int x = get<0>(l[j]);
            int y = get<1>(l[j]);
            if(visit.count({x, y})==0){
                res++;
                visit.insert({x, y});
            }
            if(get<3>(l[j])=='N'){
                get<1>(l[j])=y+1;
            } else{
                get<0>(l[j])=x+1;
            }
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<"\n";
    }
}
