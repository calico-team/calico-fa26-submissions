#include <bits/stdc++.h>
using namespace std;
long long solve(int N, long long K, const vector<tuple<int, int, int, char>>& L) {
set<pair<int, int>> eastu;
set<pair<int, int>> northu;
map<int, vector<int>> eastbs;  
map<int, vector<int>> northbs;
for (const auto& drone : L) {
    int x = get<0>(drone);
	int y = get<1>(drone);
	char d = get<3>(drone);
        if (d == 'E') {
        eastu.insert({x, y});
        eastbs[x + y].push_back(x);
        } else {
        northu.insert({x, y});
        northbs[x + y].push_back(x);
        }
    }
    long long C_E = eastu.size();
    long long C_N = northu.size();
    long long base_total = (C_E + C_N) * K;
    long long intersections = 0;
    for (auto& pairentry : eastbs) {
        int S = pairentry.first;
        if (northbs.find(S) == northbs.end()) continue;
        vector<int>& eastx = pairentry.second;
        vector<int>& northx = northbs[S];
        sort(northx.begin(), northx.end());
        for (int xe : eastx) {
            auto it1 = lower_bound(northx.begin(), northx.end(), xe);
            auto it2 = lower_bound(northx.begin(), northx.end(), xe + K);
            intersections += distance(it1, it2);
        }
    }
    return base_total - intersections;
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
        cout<<solve(N, K, L)<<endl;
    }
return 0;
}