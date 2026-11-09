#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    long long answer = (long long) N * K;
    map<int, vector<int>> north;
    vector<pair<int, int>> east;
    for (int i = 0; i < N; i++){
        auto [x, y, z, d] = L[i];
        int sum = x + y;
        if (d == 'N'){
            north[sum].push_back(x);
        } else {
            east.push_back({sum, x});
        }
    }
    for (auto &i : north){
        sort(i.second.begin(), i.second.end());
    }
    for (auto [sum, x] : east){
        if (north.count(sum) == false) continue;
        vector<int> &a = north[sum];
        auto left = lower_bound(a.begin(), a.end(), x);
        auto right = lower_bound(a.begin(), a.end(), x + K);
        answer -= right - left;
    }
    return answer;
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
}
