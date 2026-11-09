#include <bits/stdc++.h>
using namespace std;



long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    vector<pair<int, int>> east;
    for (auto& [x, y, z, d] : L)
        if (d == 'E') east.push_back({x + y, x});
    sort(east.begin(), east.end());

    long long answer = (long long)N * K;
    for (auto& [x, y, z, d] : L) {
        if (d != 'N') continue;
        answer -= upper_bound(east.begin(), east.end(), pair<int, int>{x + y, x}) -
                  lower_bound(east.begin(), east.end(), pair<int, int>{x + y, x - K + 1});
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
